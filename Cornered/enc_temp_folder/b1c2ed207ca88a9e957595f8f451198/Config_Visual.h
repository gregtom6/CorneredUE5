// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Visual.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Visual : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	float PlayerReceivedShotPostProcessMultiplier;
	UPROPERTY(EditAnywhere)
	float DeltaHealthSpeedMultiplier;
};
