// Fill out your copyright notice in the Description page of Project Settings.


#include "CorneredGameInstance.h"
#include "CorneredSaveGame.h"
#include <Kismet/GameplayStatics.h>

void UCorneredGameInstance::SaveGame(int32 unlockLevel)
{
    if (CurrentSaveGame == nullptr)
    {
        CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));
    }

    CurrentSaveGame->CurrentUnlockLevel = unlockLevel;

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, TEXT("DefaultSaveSlot"), 0);
}

void UCorneredGameInstance::LoadGame()
{
    CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("DefaultSaveSlot"), 0));

    if (CurrentSaveGame)
    {
        // TODO: Extract data from CurrentSaveGame...
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No save game found in slot"));
    }
}

void UCorneredGameInstance::ResetGame() {
    
    CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));

}

int32 UCorneredGameInstance::GetCurrentUnlockLevel() const
{
    if (CurrentSaveGame)
    {
        return CurrentSaveGame->CurrentUnlockLevel;
    }

    return 0;
}