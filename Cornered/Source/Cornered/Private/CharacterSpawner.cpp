// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CharacterSpawner.h"
#include "Engine/World.h"
#include "Engine/LevelStreaming.h"
#include "Config_Character_General.h"
#include "EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Engine/TargetPoint.h"
#include "Config_CharacterSpawner.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/TargetPoint.h"
#include "Engine/LevelStreaming.h"
#include "EnemyCharacter.h"
#include "Config_Character_General.h"

void UCharacterSpawner::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	//FWorldDelegates::LevelAddedToWorld.AddUObject(this, &UCharacterSpawner::OnLevelLoaded);
}

void UCharacterSpawner::OnLevelLoaded(ULevel* LoadedLevel, UWorld* World)
{
	/*
	if (!bLevelLoaded && IsWorldInArray(World)) {
		FVector SelectedPosition = GetRandomPosition();

		const UConfig_CharacterSpawner* Settings = GetDefault<UConfig_CharacterSpawner>();

		if (Settings) {
			AEnemyCharacter* enemyCharacter = GetWorld()->SpawnActor<AEnemyCharacter>(Settings->CharacterConfig->EnemyCharacterClass, SelectedPosition, FRotator::ZeroRotator);

			OnEnemyGenerated.Broadcast(enemyCharacter);
			bLevelLoaded = true;
		}

	}
	*/
}

void UCharacterSpawner::OnGameStart() {
	//if (!bLevelLoaded) {
		FVector SelectedPosition = GetRandomPosition();

		const UConfig_CharacterSpawner* Settings = GetDefault<UConfig_CharacterSpawner>();

		if (Settings) {
			AEnemyCharacter* enemyCharacter = GetWorld()->SpawnActor<AEnemyCharacter>(Settings->CharacterConfig->EnemyCharacterClass, SelectedPosition, FRotator::ZeroRotator);

			OnEnemyGenerated.Broadcast(enemyCharacter);
			//bLevelLoaded = true;
		}

	//}
}

bool UCharacterSpawner::ShouldCreateSubsystem(UObject* Outer) const
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

FVector UCharacterSpawner::GetRandomPosition() {
	TArray<AActor*> FoundActors = QueryAllTargetPoints();
	if (FoundActors.Num() > 0) {
		int index = FMath::RandRange(0, FoundActors.Num() - 1);
		return FoundActors[index]->GetActorLocation();
	}

	return FVector::ZeroVector;
}

bool UCharacterSpawner::IsWorldInArray(UWorld* World) const
{
	const UConfig_CharacterSpawner* Settings = GetDefault<UConfig_CharacterSpawner>();
	if (Settings)
	{
		for (int i = 0; i < Settings->ActiveInTheseLevels.Num(); i++) {
			FString name1 = RemoveBeforeUnderscore(Settings->ActiveInTheseLevels[i]->GetMapName());
			FString name2 = RemoveBeforeUnderscore(World->GetMapName());
			if (name1 == name2) {
				return true;
			}
		}
	}

	return false;
}

FString UCharacterSpawner::RemoveBeforeUnderscore(const FString& Input) const {

	int32 LastUnderscoreIndex;
	FString result;

	if (Input.FindLastChar('_', LastUnderscoreIndex))
	{
		result = Input.RightChop(LastUnderscoreIndex + 1);
		return result;
	}

	return Input;
}

TArray<AActor*> UCharacterSpawner::QueryAllTargetPoints()
{
	UWorld* World = GetWorld();
	TArray<AActor*> FoundActors;
	if (World)
	{
		UGameplayStatics::GetAllActorsOfClass(World, ATargetPoint::StaticClass(), FoundActors);
	}

	return FoundActors;
}