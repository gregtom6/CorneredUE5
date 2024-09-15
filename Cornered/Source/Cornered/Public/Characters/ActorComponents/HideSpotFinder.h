// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HideSpotFinder.generated.h"

class UConfig_AI;
class AEnemyCharacter;

USTRUCT(BlueprintType)
struct FObstacleHideSpots
{
	GENERATED_BODY()
	
public:

	AActor* ObstacleActor;

	TArray<float> Angles;

	TArray<FVector> PossibleHideSpots;

	FVector HighlightedHideSpot;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UHideSpotFinder : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TObjectPtr<AEnemyCharacter> Enemy;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_AI> AIConfig;

public:
	UHideSpotFinder();
	TOptional<FVector> GetClosestHidingSpot();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

private:
	void FindingPossiblePositionsAlongCurrentRay(FVector ImpactPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent, FVector Direction, TArray<FVector>& possibleHideSpots);

	FHitResult MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit) const;

	bool ThisRayIsNotHittingPlayer(FHitResult raycastHits) const;

	bool IsThisPointNotVisibleByPlayer(FVector CurrentPoint) const;

	bool IsThisPointOutsideColliders(FVector CurrentPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent) const;

	void SortPointsByDistance(TArray<FVector>& PointsArray);

	bool IsObstacleAlreadyFound(AActor* ObstacleActor, TArray<FObstacleHideSpots> obstacles, FObstacleHideSpots& loadedObstacleDetails, int& foundInIndex) const;

	void FillHighlightedHideSpots(TArray<FObstacleHideSpots>& obstacles);

	TArray<FVector> GetHighlightedHideSpots(TArray<FObstacleHideSpots> obstacles) const;

	int GetClosestIndex(const TArray<float>& Array, float TargetValue) const;

	float NormalizeAngle(float Angle) const;

	float CalculateCircularMean(const TArray<float>& Angles) const;
};
