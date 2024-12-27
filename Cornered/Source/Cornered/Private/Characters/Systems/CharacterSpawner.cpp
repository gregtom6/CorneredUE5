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
#include "System/ProgressionGameState.h"
#include "Characters/Systems/Soul.h"
#include "TimerManager.h"
#include "Environment/Others/SoulRoute.h"

void UCharacterSpawner::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	SoulRoute = GetSoulRoute();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
	AGameStateBase* GameState = GetWorld()->GetGameState();
	AProgressionGameState* ProgressionGameState = Cast<AProgressionGameState>(GameState);

	ProgressionGameState->CharacterDefeated.AddUniqueDynamic(this, &UCharacterSpawner::OnCharacterDefeated);
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

ASoulRoute* UCharacterSpawner::GetSoulRoute() {
	UWorld* World = GetWorld();
	TArray<AActor*> FoundActors;
	if (World)
	{
		SoulRoute= Cast<ASoulRoute>(UGameplayStatics::GetActorOfClass(World, ASoulRoute::StaticClass()));
		return SoulRoute;
	}

	return nullptr;
}

void UCharacterSpawner::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {

	DefeatedCharacter->SetDieState();

	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {

		DefeatedChar = DefeatedCharacter;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCharacterSpawner::SoulBorner, 2.0f, false);
	}
}

void UCharacterSpawner::SoulBorner() {
	const UConfig_CharacterSpawner* Settings = GetDefault<UConfig_CharacterSpawner>();

	if (Settings) {
		FVector SoulLocation = Cast<AEnemyCharacter>(DefeatedChar)->GetSoulLocation();
		ASoul* soul = GetWorld()->SpawnActor<ASoul>(Settings->SoulClass, SoulLocation, FRotator::ZeroRotator);
		soul->SetSoulRoute(SoulRoute);
	}
}