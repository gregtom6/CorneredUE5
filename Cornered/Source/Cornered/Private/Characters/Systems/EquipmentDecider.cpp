// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EquipmentDecider.h"
#include "CharacterSpawner.h"
#include "Config_Equipment.h"
#include "EnemyCharacter.h"
#include "ConfigEquipmentDevSettings.h"


void UEquipmentDecider::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->OnEnemyGenerated.AddDynamic(this, &UEquipmentDecider::OnEnemyGenerated);
	}
}

void UEquipmentDecider::OnEnemyGenerated(AEnemyCharacter* EnemyCharacter) {
	GenerateEquipment(EnemyCharacter);
}

void UEquipmentDecider::GenerateEquipment(AEnemyCharacter* EnemyCharacter) {

	const UConfigEquipmentDevSettings* Settings = GetDefault<UConfigEquipmentDevSettings>();

	if (Settings) {
		FItemDatas weapon = Settings->GetRandomWeapon();
		FItemDatas shield = Settings->GetRandomShield();
		FItemDatas additional = Settings->GetRandomAdditional();

		EnemyCharacter->SetEquipment(weapon, shield, additional);

		OnEquipmentDecided.Broadcast(weapon, shield, additional);
	}
}

bool UEquipmentDecider::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Outer || !Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	const UWorld* World = Cast<UWorld>(Outer);
	if (!World)
	{
		return false;
	}

	const TArray<TSoftObjectPtr<UWorld>>& Levels = GetDefault<UConfigEquipmentDevSettings>()->ActiveInTheseLevels;
	for (TSoftObjectPtr<UWorld> Level : Levels)
	{
		const UWorld* LevelPtr = Level.Get();
		if (LevelPtr && LevelPtr->GetName() == World->GetName())
		{
			return true;
		}
	}

	return false;
}