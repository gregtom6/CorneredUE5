// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HideSpotFinder.generated.h"

class UConfig_AI;
class AEnemyCharacter;

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

	FHitResult MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit);

	bool ThisRayIsNotHittingPlayer(FHitResult raycastHits);

	bool IsThisPointNotVisibleByPlayer(FVector CurrentPoint);

	bool IsThisPointOutsideColliders(FVector CurrentPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent);

	void SortPointsByDistance(TArray<FVector>& PointsArray);
};
