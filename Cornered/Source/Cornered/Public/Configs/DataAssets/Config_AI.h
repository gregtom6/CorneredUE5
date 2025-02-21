// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_AI.generated.h"

UCLASS()
class CORNERED_API UConfig_AI : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float AttackHideLifeBorderPercentage;

	UPROPERTY(EditAnywhere)
	float PreserveDistanceBetweenPlayerAndMe;

	UPROPERTY(EditAnywhere)
	float EnemyAttackVisionDistance;

	UPROPERTY(EditAnywhere)
	float NavmeshSamplePositionDistance;

	UPROPERTY(EditAnywhere)
	float RayTraverseStepSizeToDiscoverHidingPlace;

	UPROPERTY(EditAnywhere)
	float AngleRotationChecksToDetectHidingSpot;

	UPROPERTY(EditAnywhere)
	float RayLengthToFindObstacle;

	UPROPERTY(EditAnywhere)
	float HideSpotFinderDebugLineLifeTime;

	UPROPERTY(EditAnywhere)
	float HideSpotFinderDebugLineThickness;

	UPROPERTY(EditAnywhere)
	FVector HideSpotFinderOriginOffset;

	UPROPERTY(EditAnywhere)
	float ObstacleFindingRayStartingStepCount;

	UPROPERTY(EditAnywhere)
	float ObstacleFindingRayDeltaStepSize;

	UPROPERTY(EditAnywhere)
	float ObstacleFindingRayMaxDistance;

	UPROPERTY(EditAnywhere)
	float HideSpotDebugSphereRadius;

	UPROPERTY(EditAnywhere)
	float HideSpotDebugSphereSegments;

	UPROPERTY(EditAnywhere)
	float HideSpotDebugSphereThickness;
};
