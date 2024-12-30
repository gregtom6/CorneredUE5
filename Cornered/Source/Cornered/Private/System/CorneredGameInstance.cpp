// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredGameInstance.h"
#include "System/CorneredSaveGame.h"
#include <Kismet/GameplayStatics.h>

void UCorneredGameInstance::SaveGame(int32 unlockLevel, int32 sniffedSoulCount)
{
    if (CurrentSaveGame == nullptr)
    {
        CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));
    }

    CurrentSaveGame->CurrentUnlockLevel = unlockLevel;
    CurrentSaveGame->CurrentSniffedSouls = sniffedSoulCount;

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

int32 UCorneredGameInstance::GetCurrentSniffedSoulCount() const {
    if (CurrentSaveGame) {
        return CurrentSaveGame->CurrentSniffedSouls;
    }

    return 0;
}