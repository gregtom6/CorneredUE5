// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Soul.generated.h"

class UCurveFloat;

UCLASS()
class CORNERED_API UConfig_Soul : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float SpeedTowardsSpline;

	UPROPERTY(EditAnywhere)
	float SpeedAlongSpline;

	UPROPERTY(EditAnywhere)
	float SpeedTowardsFinalTarget;

	UPROPERTY(EditAnywhere)
	float AllowedDistanceFromPoints;

	UPROPERTY(EditAnywhere)
	float CurveReadMultiplier;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> LampBlinkingCurve;

public:

	float GetIntensityMultiplier(float Time);
};
