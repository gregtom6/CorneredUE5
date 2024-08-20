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

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

		FEnemyGeneratedDelegate OnEnemyGenerated;
private:
	UFUNCTION()
		void OnNewMatchStarted();

		FVector GetRandomPosition();

		TArray<AActor*> QueryAllTargetPoints();

	bool bLevelLoaded;

	UFUNCTION()
		void OnCharacterDefeated(ACharacter* DefeatedCharacter);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
