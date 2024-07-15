// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_ExitDoor : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		float ButtonHoldingOpenMultiplier;

	UPROPERTY(EditAnywhere)
		float MinPercentage;

	UPROPERTY(EditAnywhere)
		float MaxPercentage;
};
