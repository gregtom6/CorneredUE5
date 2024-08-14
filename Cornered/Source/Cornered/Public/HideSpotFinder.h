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
	// Sets default values for this component's properties
	UHideSpotFinder();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		TOptional<FVector> GetClosestHidingSpot();

private:

	UPROPERTY()
		TObjectPtr<AEnemyCharacter> Enemy;

	UPROPERTY(EditAnywhere)
		UConfig_AI* AIConfig;

	UFUNCTION()
		void SortHitsBasedOnDistance();

	UFUNCTION()
		void FindingPossiblePositionsAlongCurrentRay(FVector Origin, FVector Direction, TArray<FVector>& possibleHideSpots, TArray<FHitResult> raycastHits, float rayLength);

	UFUNCTION()
		TArray<FHitResult> MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction);

	UFUNCTION()
		bool ThisRayIsNotHittingPlayer(TArray<FHitResult> raycastHits);

	UFUNCTION()
		bool IsThisPointNotVisibleByPlayer(FVector CurrentPoint);

	UFUNCTION()
		bool IsThisPointOutsideColliders(FVector CurrentPoint);

	UFUNCTION()
		void SortPointsByDistance(TArray<FVector>& PointsArray);
};
