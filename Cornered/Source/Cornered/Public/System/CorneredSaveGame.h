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
	int32 CurrentUnlockLevel;

};
