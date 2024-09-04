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
		float HideWhenLifeLessThanPercentage;

	UPROPERTY(EditAnywhere)
		float AttackWhenLifeMoreThanPercentage;

	UPROPERTY(EditAnywhere)
		float PreserveDistanceBetweenPlayerAndMe;

	UPROPERTY(EditAnywhere)
		float EnemyAttackVisionDistance; //1000.f

	UPROPERTY(EditAnywhere)
		float NavmeshSamplePositionDistance;

	UPROPERTY(EditAnywhere)
		float RayTraverseStepSizeToDiscoverHidingPlace;

	UPROPERTY(EditAnywhere)
		float AngleRotationChecksToDetectHidingSpot; //10.f

	UPROPERTY(EditAnywhere)
		float RayLengthToFindObstacle; //1500.f

	UPROPERTY(EditAnywhere)
		float HideSpotFinderDebugLineLifeTime; // 0.001f

	UPROPERTY(EditAnywhere)
		float HideSpotFinderDebugLineThickness; //2.0f

	UPROPERTY(EditAnywhere)
		FVector HideSpotFinderOriginOffset; //FVector(0.f, 0.f, 100.f)

	UPROPERTY(EditAnywhere)
		float ObstacleFindingRayStartingStepCount; //5.f

	UPROPERTY(EditAnywhere)
		float ObstacleFindingRayDeltaStepSize; //1.f

	UPROPERTY(EditAnywhere)
		float ObstacleFindingRayMaxDistance; //5000.f

	UPROPERTY(EditAnywhere)
		float HideSpotDebugSphereRadius; //100.f

	UPROPERTY(EditAnywhere)
		float HideSpotDebugSphereSegments; //12

	UPROPERTY(EditAnywhere)
		float HideSpotDebugSphereThickness; //1.0f
};
