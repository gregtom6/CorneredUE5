// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CorneredGameMode.generated.h"

class UConfig_Time;
class ACorneredCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeOverHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNewMatchStartedDelegate);

UCLASS()
class CORNERED_API ACorneredGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	FTimeOverHappenedDelegate TimeOverHappened;

	FNewMatchStartedDelegate NewMatchStarted;

private:

	float StartTime;

	bool bIsPreparingTime;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Time> TimeConfig;

	FTimerHandle TimerHandle;

public:

	void RestartTimer();

	void ZeroingTimer();

	UFUNCTION(BlueprintPure)
	float GetPreparingTimeLeft() const;


	virtual void StartPlay() override;


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void PreparingTimeEnded();

	UFUNCTION()
	void WaitUntilGameOverEnded();

	UFUNCTION()
	void WaitTimeEndedBetweenMatches();

private:

	UFUNCTION()
	void CharacterDied(ACorneredCharacter* Character);

	void InitiateNewMatch();

	void InitiateGameOver();
};
