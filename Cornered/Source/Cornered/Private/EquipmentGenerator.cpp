// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EquipmentGenerator.h"
#include "CharacterSpawner.h"
#include "Config_Equipment.h"
#include "EnemyCharacter.h"

// Sets default values
AEquipmentGenerator::AEquipmentGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEquipmentGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->OnEnemyGenerated.AddDynamic(this, &AEquipmentGenerator::OnEnemyGenerated);
	}
}

// Called every frame
void AEquipmentGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipmentGenerator::OnEnemyGenerated(AEnemyCharacter* EnemyCharacter) {
	GenerateEquipment(EnemyCharacter);
}

void AEquipmentGenerator::GenerateEquipment(AEnemyCharacter* EnemyCharacter) {
	FItemDatas weapon= EquipmentConfig->GetRandomWeapon();
	FItemDatas shield = EquipmentConfig->GetRandomShield();
	FItemDatas additional = EquipmentConfig->GetRandomAdditional();

	EnemyCharacter->SetEquipment(weapon, shield, additional);
}