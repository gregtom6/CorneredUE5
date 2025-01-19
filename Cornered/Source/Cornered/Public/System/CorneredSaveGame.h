// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CorneredSaveGame.generated.h"

/**
 *
 */
UCLASS()
class CORNERED_API UCorneredSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 CurrentLevel;
	UPROPERTY(EditAnywhere)
	float OpeningProgress;
	UPROPERTY(EditAnywhere)
	int32 CurrentUnlockLevel;
	UPROPERTY(EditAnywhere)
	int32 SniffedSoulsInCurrentLevel;
	UPROPERTY(EditAnywhere)
	int32 CurrentSniffedSoulsGlobal;
	UPROPERTY(EditAnywhere)
	int32 CurrentOverloadSoulsGlobal;
};
