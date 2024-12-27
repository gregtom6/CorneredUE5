// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CharacterSpawner.generated.h"


class UConfig_CharacterSpawner;
class ATargetPoint;
class AEnemyCharacter;
class ACorneredCharacter;
class UConfig_Character_General;
class ASoulRoute;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyGeneratedDelegate, AEnemyCharacter*, EnemyCharacter);

UCLASS()
class CORNERED_API UCharacterSpawner : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	FEnemyGeneratedDelegate OnEnemyGenerated;

private:

	bool bLevelLoaded;

	FTimerHandle TimerHandle;

	ACorneredCharacter* DefeatedChar = nullptr;

	ASoulRoute* SoulRoute = nullptr;

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UFUNCTION()
	void OnNewMatchStarted();

	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);

	FVector GetRandomPosition() const;

	TArray<AActor*> QueryAllTargetPoints() const;

	ASoulRoute* GetSoulRoute();

	void SoulBorner();
};
