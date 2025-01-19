// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredGameInstance.h"
#include "System/CorneredSaveGame.h"
#include <Kismet/GameplayStatics.h>
#include "System/ProgressionGameState.h"

void UCorneredGameInstance::SaveGame(int32 currentLevel, int32 unlockLevel, float openingProgress, int32 sniffedSoulCount, int32 sniffedSoulsGlobalCount, int32 sniffedOverloadGlobalCount)
{
    if (CurrentSaveGame == nullptr)
    {
        CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));
    }

    CurrentSaveGame->CurrentLevel = currentLevel;
    CurrentSaveGame->OpeningProgress = openingProgress;
    CurrentSaveGame->CurrentUnlockLevel = unlockLevel;
    CurrentSaveGame->SniffedSoulsInCurrentLevel = sniffedSoulCount;
    CurrentSaveGame->CurrentSniffedSoulsGlobal = sniffedSoulsGlobalCount;
    CurrentSaveGame->CurrentOverloadSoulsGlobal = sniffedOverloadGlobalCount;

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, TEXT("DefaultSaveSlot"), 0);
}

void UCorneredGameInstance::SaveOpeningProgress(float openingProgress) {
    if (CurrentSaveGame == nullptr)
    {
        CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));
    }

    CurrentSaveGame->OpeningProgress = openingProgress;

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, TEXT("DefaultSaveSlot"), 0);
}

void UCorneredGameInstance::SaveUnlockLevel(int32 unlockLevel) {
    if (CurrentSaveGame == nullptr)
    {
        CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));
    }

    CurrentSaveGame->CurrentUnlockLevel = unlockLevel;

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, TEXT("DefaultSaveSlot"), 0);
}

void UCorneredGameInstance::SaveSniffedSoulCount(int32 sniffedSoulCount) {
    if (CurrentSaveGame == nullptr)
    {
        CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));
    }

    CurrentSaveGame->SniffedSoulsInCurrentLevel = sniffedSoulCount;

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, TEXT("DefaultSaveSlot"), 0);
}

void UCorneredGameInstance::SaveEndLevelStats(AProgressionGameState* GameState) {
    if (CurrentSaveGame == nullptr)
    {
        CurrentSaveGame = Cast<UCorneredSaveGame>(UGameplayStatics::CreateSaveGameObject(UCorneredSaveGame::StaticClass()));
    }

    CurrentSaveGame->CurrentLevel += 1;
    CurrentSaveGame->OpeningProgress = 0.f;
    CurrentSaveGame->CurrentUnlockLevel = 0;
    CurrentSaveGame->CurrentSniffedSoulsGlobal += CurrentSaveGame->SniffedSoulsInCurrentLevel;
    CurrentSaveGame->CurrentOverloadSoulsGlobal += GameState->GetCurrentOverloadSoulCount();
    CurrentSaveGame->SniffedSoulsInCurrentLevel = 0;

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


int32 UCorneredGameInstance::GetCurrentLevel() const {
    if (CurrentSaveGame) {
        return CurrentSaveGame->CurrentLevel;
    }

    return 0;
}

int32 UCorneredGameInstance::GetCurrentUnlockLevel() const
{
    if (CurrentSaveGame)
    {
        return CurrentSaveGame->CurrentUnlockLevel;
    }

    return 0;
}

float UCorneredGameInstance::GetCurrentOpeningProgress() const {
    if (CurrentSaveGame) {
        return CurrentSaveGame->OpeningProgress;
    }

    return 0.f;
}