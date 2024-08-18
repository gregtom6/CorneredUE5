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
	
public:

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void SaveGame(int32 unlockLevel);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		void ResetGame();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		int32 GetCurrentUnlockLevel() const;

private:

	UPROPERTY()
		TObjectPtr<UCorneredSaveGame> CurrentSaveGame;

};
