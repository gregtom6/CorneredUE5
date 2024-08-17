// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CorneredGameMode.h"
#include <CorneredHud.h>
#include <Kismet/GameplayStatics.h>
#include "Config_Time.h"
#include "CharacterSpawner.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.h"
#include "LevelManager.h"
#include "ConfigLevelsDevSettings.h"

ACorneredGameMode::ACorneredGameMode()
{

}

void ACorneredGameMode::StartPlay()
{
	Super::StartPlay();

	InitiateNewMatch();
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

void ACorneredGameMode::WaitTimeEndedBetweenMatches() {
	InitiateNewMatch();
}

void ACorneredGameMode::CharacterDied(ACharacter* Character) {
	CharacterDefeated.Broadcast(Character);

	if (Character->IsA(AEnemyCharacter::StaticClass())) {
		MatchIndex += 1;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACorneredGameMode::WaitTimeEndedBetweenMatches, TimeConfig->WaitBetweenPreviousAndNewMatchInSec, false);
	}
	else {
		InitiateGameOver();
	}
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

void ACorneredGameMode::InitiateNewMatch() {
	NewMatchStarted.Broadcast();
}

void ACorneredGameMode::InitiateGameOver() {
	ULevelManager* MySubsystem = GetGameInstance()->GetSubsystem<ULevelManager>();
	MySubsystem->LoadLevel(ELevelIdentifier::GameOverScene, GetWorld());
}