// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CorneredGameMode.generated.h"

class UConfig_Time;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimeOverHappenedDelegate);

/**
 * 
 */
UCLASS()
class CORNERED_API ACorneredGameMode : public AGameModeBase
{
	GENERATED_BODY()

		ACorneredGameMode();

protected:
	virtual void BeginPlay() override;

	void PreparingTimeEnded();

public:

	UFUNCTION()
	void RestartTimer();

	UFUNCTION()
		void ZeroingTimer();

	UFUNCTION()
		float GetPreparingTimeLeft();

	UPROPERTY()
		FTimeOverHappenedDelegate TimeOverHappened;

private:

	UPROPERTY()
	float StartTime;

	UPROPERTY()
		bool bIsPreparingTime;

	UPROPERTY(EditAnywhere)
		UConfig_Time* TimeConfig;

	FTimerHandle TimerHandle;
};
