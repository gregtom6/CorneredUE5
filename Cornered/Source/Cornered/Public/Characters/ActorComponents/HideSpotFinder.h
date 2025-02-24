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

	UPROPERTY()
	TObjectPtr<AActor> ObstacleActor;

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

	int32 asyncPathQueryCount;

public:
	UHideSpotFinder();
	
	void ManageDebugDrawings(bool enabled);

	void RegisterCallback(FHideSpotSearchingEnded HideSpotSearchingEnded);

	void GetClosestHidingSpotAsync();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

private:
	void OnPathFound(uint32 PathRequestID, ENavigationQueryResult::Type Result, FNavPathSharedPtr Path);

	void DrawDebug(FVector FinalSelectedHideSpot);

	void DrawDebugLines(FVector Origin, FVector End) const;

	bool IsPossibleHideSpotSetted(int32 location, int32 position);

	bool AreAllPossibleHideSpotsSetted(int32 location);

	bool IsPossibleHideSpotFoundInThisAngle(AActor* Obstacle, float CurrentlyCheckedAngle);

	float GetBackAngleOfPathRequestID(AActor* Obstacle, uint32 PathRequestID);

	int32 GetLocationOfAngleHideouts(int32 location, float CurrentAngle);

	void StoreGeneralObstacleDetails(FHitResult raycastHits, float CurrentAngle, int32 foundInIndex);

	bool GetBackObstacleDetailsWherePathRequestID(uint32 PathRequestID, int32& location);

	void FindingPossibleHideSpotAlongCurrentRayAsync(FVector ImpactPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent, FVector Direction, int32 foundInIndex, float CurrentlyCheckedAngle, AActor* Obstacle);

	FHitResult MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit) const;

	bool ThisRayIsNotHittingPlayer(FHitResult raycastHits) const;

	bool DidIFindObstacle(bool Hit, FHitResult raycastHits) const;

	int32 LoadObstacleDetailsIfExists(FHitResult raycastHits);

	bool AreTherePossibleHideSpots(TArray<FObstacleHideSpots> possibleHideSpots) const;

	bool IsThisPointNotVisibleByPlayer(FVector CurrentPoint) const;

	void ProcessingPossibleHideSpots();

	bool IsThisPointOutsideColliders(FVector CurrentPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent) const;

	void SortPointsByDistance(TArray<FVector>& PointsArray);

	bool IsObstacleAlreadyFoundInPreviousAngle(AActor* ObstacleActor, TArray<FObstacleHideSpots> obstacles, int32& foundInIndex) const;

	void SetBestHideSpotsForAllObstacles(TArray<FObstacleHideSpots>& obstacles);

	TArray<FVector> GetBestHideSpots(TArray<FObstacleHideSpots> obstacles) const;

	int32 GetClosestIndex(const TArray<float>& Array, float TargetValue) const;

	float NormalizeAngle(float Angle) const;

	float CalculateCircularMean(const TArray<float>& Angles) const;
};
