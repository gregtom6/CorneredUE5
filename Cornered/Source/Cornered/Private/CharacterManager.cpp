// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CharacterManager.h"
#include "Config_Character_General.h"
#include "EnemyCharacter.h"

// Sets default values
ACharacterManager::ACharacterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterManager::BeginPlay()
{
	Super::BeginPlay();
	
	FVector SelectedPosition = GetRandomPosition();
	GetWorld()->SpawnActor<AEnemyCharacter>(CharacterConfig->EnemyCharacterClass, SelectedPosition, FRotator::ZeroRotator);
}

// Called every frame
void ACharacterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ACharacterManager::GetRandomPosition() {
	int index= FMath::RandRange(0, EnemyPossibleStartingPositions.Num()-1);
	return EnemyPossibleStartingPositions[index]->GetActorLocation();
}