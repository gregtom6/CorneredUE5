// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HideSpotFinder.generated.h"

class UConfig_AI;
class AEnemyCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UHideSpotFinder : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHideSpotFinder();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

public:	

		TOptional<FVector> GetClosestHidingSpot();

private:

	UPROPERTY()
		TObjectPtr<AEnemyCharacter> Enemy;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_AI> AIConfig;

		void FindingPossiblePositionsAlongCurrentRay(FVector ImpactPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent, FVector Direction, TArray<FVector>& possibleHideSpots);

		FHitResult MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit);

		bool ThisRayIsNotHittingPlayer(FHitResult raycastHits);

		bool IsThisPointNotVisibleByPlayer(FVector CurrentPoint);

		bool IsThisPointOutsideColliders(FVector CurrentPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent);

		void SortPointsByDistance(TArray<FVector>& PointsArray);
};
