// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CorneredGameInstance.generated.h"

class UCorneredSaveGame;
class AProgressionGameState;

/**
 *
 */
UCLASS()
class CORNERED_API UCorneredGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TObjectPtr<UCorneredSaveGame> CurrentSaveGame;

public:
	void SaveGame(int32 currentLevel, int32 unlockLevel, float openingProgress, int32 sniffedSoulCount, int32 sniffedSoulsGlobalCount, int32 sniffedOverloadGlobalCount);
	void SaveOpeningProgress(float openingProgress);
	void SaveUnlockLevel(int32 unlockLevel);
	void SaveSniffedSoulCount(int32 sniffedSoulCount);
	void SaveEndLevelStats(AProgressionGameState* GameState);

	void LoadGame();

	void ResetGame();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentLevel() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentUnlockLevel() const;

	UFUNCTION(BlueprintPure)
	float GetCurrentOpeningProgress() const;
};
