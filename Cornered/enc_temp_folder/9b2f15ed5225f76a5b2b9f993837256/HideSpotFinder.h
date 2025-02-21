// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavigationSystem.h"
#include "HideSpotFinder.generated.h"

class UConfig_AI;
class AEnemyCharacter;
class UNavigationSystemV1;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHideSpotSearchingEnded, FVector, Result, bool, bIsValid);

USTRUCT(BlueprintType)
struct FAngleAndItsPossibleHideSpot {
	GENERATED_BODY()

public:

	float Angle;

	TOptional<FVector> PossibleHideSpot;
	TArray<uint32> PathRequestIDs;
};

USTRUCT(BlueprintType)
struct FObstacleHideSpots
{
	GENERATED_BODY()
	
public:

	AActor* ObstacleActor;

	TArray<FAngleAndItsPossibleHideSpot> AnglesAndPossibleHideSpots;

	FVector BestHideSpot;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UHideSpotFinder : public UActorComponent
{
	GENERATED_BODY()

public:

	FHideSpotSearchingEnded HideSpotSearchingEnded;

private:

	UPROPERTY()
	TObjectPtr<AEnemyCharacter> Enemy;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_AI> AIConfig;

	UNavigationSystemV1* NavSystem;

	TArray<FObstacleHideSpots> obstacleCheckDetails;

	bool bDidFindPossibleHideSpotAlongThisRay;
	bool bCanLookForNewHidingSpot;
	float stepCount;

	float currentlyCheckedAngle;

	UPROPERTY(EditAnywhere)
	bool bDrawDebug;

	int testInteger;

public:
	
	void ManageDebugDrawings(bool enabled);

	void RegisterCallback(FHideSpotSearchingEnded HideSpotSearchingEnded);

	void OnPathFound(uint32 PathRequestID, ENavigationQueryResult::Type Result, FNavPathSharedPtr Path);

public:
	UHideSpotFinder();
	void GetClosestHidingSpotAsync();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

private:

	void DrawDebug(FVector FinalSelectedHideSpot);

	void DrawDebugLines(FVector Origin, FVector End) const;

	bool IsPossibleHideSpotSetted(int location, int position);

	bool AreAllPossibleHideSpotsSetted(int location);

	bool IsPossibleHideSpotFoundInThisAngle(AActor* Obstacle, float CurrentlyCheckedAngle);

	float GetBackAngleOfPathRequestID(AActor* Obstacle, uint32 PathRequestID);

	int GetLocationOfAngleHideouts(int location, float CurrentAngle);

	void StoreGeneralObstacleDetails(FHitResult raycastHits, float CurrentAngle, int foundInIndex);

	bool GetBackObstacleDetailsWherePathRequestID(uint32 PathRequestID, int& location);

	void FindingPossibleHideSpotAlongCurrentRayAsync(FVector ImpactPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent, FVector Direction, int foundInIndex, float CurrentlyCheckedAngle, AActor* Obstacle);

	FHitResult MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit) const;

	bool ThisRayIsNotHittingPlayer(FHitResult raycastHits) const;

	bool DidIFindObstacle(bool Hit, FHitResult raycastHits) const;

	int LoadObstacleDetailsIfExists(FHitResult raycastHits);

	bool AreTherePossibleHideSpots(TArray<FObstacleHideSpots> possibleHideSpots) const;

	bool IsThisPointNotVisibleByPlayer(FVector CurrentPoint) const;

	void ProcessingPossibleHideSpots();

	bool IsThisPointOutsideColliders(FVector CurrentPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent) const;

	void SortPointsByDistance(TArray<FVector>& PointsArray);

	bool IsObstacleAlreadyFoundInPreviousAngle(AActor* ObstacleActor, TArray<FObstacleHideSpots> obstacles, int& foundInIndex) const;

	void SetBestHideSpotsForAllObstacles(TArray<FObstacleHideSpots>& obstacles);

	TArray<FVector> GetBestHideSpots(TArray<FObstacleHideSpots> obstacles) const;

	int GetClosestIndex(const TArray<float>& Array, float TargetValue) const;

	float NormalizeAngle(float Angle) const;

	float CalculateCircularMean(const TArray<float>& Angles) const;
};
