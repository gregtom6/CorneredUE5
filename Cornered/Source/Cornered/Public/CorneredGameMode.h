// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CorneredGameMode.generated.h"

class UConfig_Time;
class ACharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeOverHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDefeatedDelegate, ACharacter*, Character);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewMatchStartedDelegate);

/**
 * 
 */
UCLASS()
class CORNERED_API ACorneredGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void PreparingTimeEnded();

	void WaitTimeEndedBetweenMatches();

public:

	UFUNCTION()
	void RestartTimer();

	UFUNCTION()
		void ZeroingTimer();

	UFUNCTION()
		float GetPreparingTimeLeft();

	UPROPERTY()
		FTimeOverHappenedDelegate TimeOverHappened;

	UPROPERTY()
		FCharacterDefeatedDelegate CharacterDefeated;

	UPROPERTY()
		FNewMatchStartedDelegate NewMatchStarted;

	virtual void StartPlay() override;

	UFUNCTION()
		void CharacterDied(ACharacter* Character);

private:

	UPROPERTY()
	float StartTime;

	UPROPERTY()
		bool bIsPreparingTime;

	UPROPERTY(EditAnywhere)
		UConfig_Time* TimeConfig;

	FTimerHandle TimerHandle;

	UPROPERTY()
		int MatchIndex;

	UFUNCTION()
		void InitiateNewMatch();

	UFUNCTION()
		void InitiateGameOver();
};
