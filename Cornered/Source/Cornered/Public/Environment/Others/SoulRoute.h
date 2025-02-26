// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulRoute.generated.h"

class USceneComponent;
class USplineComponent;

UCLASS()
class CORNERED_API ASoulRoute : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComp;
	
public:	
	ASoulRoute();

	FVector GetSplinePoint(int32 index) const;

	FVector GetClosestSplinePoint(FVector Position);

	int32 GetIndexOfSplinePoint(FVector point);

	FVector GetLocationAtDistanceAlongSpline(float distance);

	float GetDistanceAlongSplineAtSplinePoint(int32 index);

	float GetRouteLengthOnSpline(FVector StartPos);

protected:

	virtual void BeginPlay() override;

};