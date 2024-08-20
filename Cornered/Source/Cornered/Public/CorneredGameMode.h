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

	UFUNCTION()
	void PreparingTimeEnded();

	UFUNCTION()
	void WaitTimeEndedBetweenMatches();

public:

	void RestartTimer();

		void ZeroingTimer();

	UFUNCTION(BlueprintPure)
		float GetPreparingTimeLeft();

		FTimeOverHappenedDelegate TimeOverHappened;

		FCharacterDefeatedDelegate CharacterDefeated;

		FNewMatchStartedDelegate NewMatchStarted;

	virtual void StartPlay() override;

		void CharacterDied(ACharacter* Character);

private:

	float StartTime;

		bool bIsPreparingTime;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Time> TimeConfig;

	FTimerHandle TimerHandle;

		int MatchIndex;

		void InitiateNewMatch();

		void InitiateGameOver();
};
