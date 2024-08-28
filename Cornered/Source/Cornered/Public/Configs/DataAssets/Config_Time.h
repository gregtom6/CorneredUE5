// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Time.generated.h"

/**
 *
 */
UCLASS()
class CORNERED_API UConfig_Time : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		float PrepareTimeEndInSec;

	UPROPERTY(EditAnywhere)
		float WaitBetweenPreviousAndNewMatchInSec;
};
