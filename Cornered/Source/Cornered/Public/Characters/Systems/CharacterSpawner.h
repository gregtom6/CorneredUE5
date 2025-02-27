// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CharacterSpawner.generated.h"


class UConfigCharacterSpawnerDevSettings;
class ATargetPoint;
class AEnemyCharacter;
class ACorneredCharacter;
class UConfig_Character_General;
class ASoulRoute;
class ASoulSniffer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyGeneratedDelegate, AEnemyCharacter*, EnemyCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoulGeneratedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoulDissipatedDelegate);

UCLASS()
class CORNERED_API UCharacterSpawner : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	FEnemyGeneratedDelegate OnEnemyGenerated;
	FSoulGeneratedDelegate OnSoulGenerated;
	FSoulDissipatedDelegate OnSoulDissipated;

private:

	bool bLevelLoaded;

	FTimerHandle TimerHandle;

	UPROPERTY()
	TObjectPtr<ACorneredCharacter> DefeatedChar = nullptr;

	UPROPERTY()
	TObjectPtr<ASoulRoute> SoulRoute = nullptr;

	UPROPERTY()
	TObjectPtr<ASoulSniffer> SoulSniffer = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<ATargetPoint>> TargetPoints;

public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	void SetSoulRoute(ASoulRoute* soulRoute);
	void SetTargetPoint(ATargetPoint* targetPoint);
	void SetSoulSniffer(ASoulSniffer* soulSniffer);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	UFUNCTION()
	void OnNewMatchStarted();

	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);

	UFUNCTION()
	void OnSoulDestroyed();

	FVector GetRandomPosition() const;

	TArray<AActor*> QueryAllTargetPoints() const;

	ASoulRoute* GetSoulRoute();

	void SoulBorner();
};
