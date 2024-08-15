// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_AI.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_AI : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		float HideWhenLifeLessThanPercentage;

	UPROPERTY(EditAnywhere)
		float AttackWhenLifeMoreThanPercentage;

	UPROPERTY(EditAnywhere)
		float PreserveDistanceBetweenPlayerAndMe;

	UPROPERTY(EditAnywhere)
		float NavmeshSamplePositionDistance;

	UPROPERTY(EditAnywhere)
		float RayTraverseStepSizeToDiscoverHidingPlace;
};
