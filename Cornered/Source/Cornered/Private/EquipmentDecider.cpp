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
	if (Outer)
	{
		UWorld* World = Outer->GetWorld();
		if (World)
		{
			// Check if running in the editor and if the editor is simulating gameplay
#if WITH_EDITOR
			if (GIsEditor)
			{
				// Check if we are in PIE (Play In Editor) mode
				if (World->IsPlayInEditor())
				{
					return IsWorldInArray(World);
				}
				return false;
			}
#else
// For packaged builds, simply check the valid worlds
			return IsWorldInArray(World);
#endif
		}
	}
	return false;
}

bool UEquipmentDecider::IsWorldInArray(UWorld* World) const
{
	const UConfigEquipmentDevSettings* Settings = GetDefault<UConfigEquipmentDevSettings>();
	if (Settings)
	{
		for (int i = 0; i < Settings->ActiveInTheseLevels.Num(); i++) {
			FString path1 = Settings->ActiveInTheseLevels[i].ToSoftObjectPath().ToString();
			FString path2 = World->GetMapName();
			if (path1 == path2) {
				return true;
			}
		}
	}

	return false;
}

FString UEquipmentDecider::RemoveBeforeUnderscore(const FString& Input) const {

	int32 LastUnderscoreIndex;
	FString result;

	if (Input.FindLastChar('_', LastUnderscoreIndex))
	{
		result = Input.RightChop(LastUnderscoreIndex + 1);
		return result;
	}

	return Input;
}