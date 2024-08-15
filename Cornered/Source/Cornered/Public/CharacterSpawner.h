// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CharacterSpawner.generated.h"


class UConfig_CharacterSpawner;
class ATargetPoint;
class AEnemyCharacter;
class UConfig_Character_General;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyGeneratedDelegate, AEnemyCharacter*, EnemyCharacter);
/**
 * 
 */
UCLASS()
class CORNERED_API UCharacterSpawner : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void OnLevelLoaded(ULevel* LoadedLevel, UWorld* World);

	UPROPERTY()
		FEnemyGeneratedDelegate OnEnemyGenerated;
	UFUNCTION()
		void OnGameStart();
private:

	bool IsWorldInArray(UWorld* World) const;

	UFUNCTION()
		FVector GetRandomPosition();

	UFUNCTION()
		TArray<AActor*> QueryAllTargetPoints();

	bool bLevelLoaded;

	UFUNCTION()
		FString RemoveBeforeUnderscore(const FString& Input) const;

};