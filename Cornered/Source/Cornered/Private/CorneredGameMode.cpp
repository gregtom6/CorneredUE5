// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CorneredGameMode.h"
#include <CorneredHud.h>
#include <Kismet/GameplayStatics.h>
#include "Config_Time.h"

ACorneredGameMode::ACorneredGameMode()
{

}

void ACorneredGameMode::BeginPlay()
{
	Super::BeginPlay();

	RestartTimer();
}

void ACorneredGameMode::RestartTimer() {

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACorneredGameMode::PreparingTimeEnded, TimeConfig->PrepareTimeEndInSec, false);
}

void ACorneredGameMode::PreparingTimeEnded() {
	TimeOverHappened.Broadcast();
}

void ACorneredGameMode::ZeroingTimer() {
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	PreparingTimeEnded();
}

float ACorneredGameMode::GetPreparingTimeLeft() {

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
		return GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle);
	}
	return 0.f;
}