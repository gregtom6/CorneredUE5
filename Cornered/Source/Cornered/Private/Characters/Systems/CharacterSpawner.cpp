// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/CharacterSpawner.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Configs/DataAssets/Config_Character_General.h"
#include "Characters/Systems/EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/TargetPoint.h"
#include "Configs/DeveloperSettings/Config_CharacterSpawner.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/TargetPoint.h"
#include "Engine/LevelStreaming.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Configs/DataAssets/Config_Character_General.h"
#include "System/CorneredGameMode.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

void UCharacterSpawner::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	CorneredGameMode->CharacterDefeated.AddUniqueDynamic(this, &UCharacterSpawner::OnCharacterDefeated);
	CorneredGameMode->NewMatchStarted.AddUniqueDynamic(this, &UCharacterSpawner::OnNewMatchStarted);
}

void UCharacterSpawner::OnNewMatchStarted() {

	FVector SelectedPosition = GetRandomPosition();

	const UConfig_CharacterSpawner* Settings = GetDefault<UConfig_CharacterSpawner>();

	if (Settings) {
		AEnemyCharacter* enemyCharacter = GetWorld()->SpawnActor<AEnemyCharacter>(Settings->CharacterConfig->EnemyCharacterClass, SelectedPosition, FRotator::ZeroRotator);

		OnEnemyGenerated.Broadcast(enemyCharacter);
	}
}

bool UCharacterSpawner::ShouldCreateSubsystem(UObject* Outer) const
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

	const TArray<TSoftObjectPtr<UWorld>>& Levels = GetDefault<UConfig_CharacterSpawner>()->ActiveInTheseLevels;
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

FVector UCharacterSpawner::GetRandomPosition() const {
	TArray<AActor*> FoundActors = QueryAllTargetPoints();
	if (FoundActors.Num() > 0) {
		int index = FMath::RandRange(0, FoundActors.Num() - 1);
		return FoundActors[index]->GetActorLocation();
	}

	return FVector::ZeroVector;
}

TArray<AActor*> UCharacterSpawner::QueryAllTargetPoints() const
{
	UWorld* World = GetWorld();
	TArray<AActor*> FoundActors;
	if (World)
	{
		UGameplayStatics::GetAllActorsOfClass(World, ATargetPoint::StaticClass(), FoundActors);
	}

	return FoundActors;
}

void UCharacterSpawner::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {
	/*
	if (DefeatedCharacter->IsA(AEnemyCharacter::StaticClass())) {
		DefeatedCharacter->Destroy();
	}
	*/

	DefeatedCharacter->SetDieState();
}