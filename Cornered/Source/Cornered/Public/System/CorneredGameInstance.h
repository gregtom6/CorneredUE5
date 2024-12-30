// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CorneredGameInstance.generated.h"

class UCorneredSaveGame;

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

	void SaveGame(int32 unlockLevel, int32 sniffedSoulCount);

	void LoadGame();

	void ResetGame();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentUnlockLevel() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentSniffedSoulCount() const;
};
