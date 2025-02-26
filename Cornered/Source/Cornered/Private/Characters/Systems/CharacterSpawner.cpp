// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/CharacterSpawner.h"
#include "Configs/DataAssets/Config_Character_General.h"
#include "Characters/Systems/EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/TargetPoint.h"
#include "Configs/DeveloperSettings/ConfigCharacterSpawnerDevSettings.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/LevelStreaming.h"
#include "System/CorneredGameMode.h"
#include "GameFramework/Character.h"
#include "System/ProgressionGameState.h"
#include "Characters/Systems/Soul.h"
#include "TimerManager.h"
#include "Environment/Others/SoulRoute.h"
#include "Environment/Others/SoulSniffer.h"

void UCharacterSpawner::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
	AGameStateBase* GameState = GetWorld()->GetGameState();
	AProgressionGameState* ProgressionGameState = Cast<AProgressionGameState>(GameState);

	ProgressionGameState->CharacterDefeated.AddUniqueDynamic(this, &UCharacterSpawner::OnCharacterDefeated);
	CorneredGameMode->NewMatchStarted.AddUniqueDynamic(this, &UCharacterSpawner::OnNewMatchStarted);
}

void UCharacterSpawner::OnNewMatchStarted() {

	FVector SelectedPosition = GetRandomPosition();

	const UConfigCharacterSpawnerDevSettings* Settings = GetDefault<UConfigCharacterSpawnerDevSettings>();

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

	const TArray<TSoftObjectPtr<UWorld>>& Levels = GetDefault<UConfigCharacterSpawnerDevSettings>()->ActiveInTheseLevels;
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

	DefeatedCharacter->SetDieState();

	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {

		DefeatedChar = DefeatedCharacter;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCharacterSpawner::SoulBorner, 2.0f, false);
	}
}

void UCharacterSpawner::SoulBorner() {
	const UConfigCharacterSpawnerDevSettings* Settings = GetDefault<UConfigCharacterSpawnerDevSettings>();

	if (Settings) {
		FVector SoulLocation = Cast<AEnemyCharacter>(DefeatedChar)->GetSoulLocation();
		ASoul* soul = GetWorld()->SpawnActor<ASoul>(Settings->SoulClass, SoulLocation, FRotator::ZeroRotator);
		soul->SetSoulRoute(SoulRoute);
		soul->SetSoulSniffer(SoulSniffer);
		OnSoulGenerated.Broadcast();

		soul->OnSoulDestroyed.AddUniqueDynamic(this, &UCharacterSpawner::OnSoulDestroyed);
	}
}

void UCharacterSpawner::OnSoulDestroyed() {
	OnSoulDissipated.Broadcast();
}

void UCharacterSpawner::SetSoulRoute(ASoulRoute* soulRoute) {
	SoulRoute = soulRoute;
}

void UCharacterSpawner::SetTargetPoint(ATargetPoint* targetPoint) {
	TargetPoints.Add(targetPoint);
}

void UCharacterSpawner::SetSoulSniffer(ASoulSniffer* soulSniffer) {
	SoulSniffer=soulSniffer;
}