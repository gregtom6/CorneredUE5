// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/HideSpotFinder.h"
#include "Configs/DataAssets/Config_AI.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Algo/Sort.h"
#include "Characters/Systems/CharacterSpawner.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Characters/Systems/PlayerCharacter.h"

UHideSpotFinder::UHideSpotFinder()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHideSpotFinder::BeginPlay()
{
	Super::BeginPlay();

	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->OnEnemyGenerated.AddDynamic(this, &UHideSpotFinder::OnEnemyGenerated);
	}
}

void UHideSpotFinder::OnEnemyGenerated(AEnemyCharacter* EnemyCharacter) {
	Enemy = EnemyCharacter;
}

void UHideSpotFinder::FindingPossiblePositionsAlongCurrentRay(FVector ImpactPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent, FVector Direction, TArray<FVector>& possibleHideSpots) {
	float currentDistanceToCheckOnRay = 0.f;
	float stepCount = AIConfig->ObstacleFindingRayStartingStepCount;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	do
	{
		currentDistanceToCheckOnRay = AIConfig->RayTraverseStepSizeToDiscoverHidingPlace * stepCount;

		if (currentDistanceToCheckOnRay >= AIConfig->ObstacleFindingRayMaxDistance)
		{
			continue;
		}

		FVector currentPoint = ImpactPoint + (Direction * currentDistanceToCheckOnRay);

		FVector extent = FVector(AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance);

		FNavLocation ClosestNavmeshPoint;

		bool navQuest = NavSystem->ProjectPointToNavigation(currentPoint, ClosestNavmeshPoint, extent);

		if (IsThisPointOutsideColliders(currentPoint, ImpactedComponent) && IsThisPointNotVisibleByPlayer(currentPoint) && navQuest)
		{
			possibleHideSpots.Add(ClosestNavmeshPoint.Location);
			break;
		}
		else
		{
			stepCount += AIConfig->ObstacleFindingRayDeltaStepSize;
		}
	} while (currentDistanceToCheckOnRay < AIConfig->ObstacleFindingRayMaxDistance);
}

FHitResult UHideSpotFinder::MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit) const {

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(PlayerController->GetPawn());

	UCameraComponent* cameraComp = PlayerPawn->FindComponentByClass<UCameraComponent>();

	Origin = cameraComp->GetComponentLocation() + AIConfig->HideSpotFinderOriginOffset;

	FVector forwardVector = cameraComp->GetForwardVector();

	FRotator rotation(0.0f, CurrentAngle, 0.0f);

	FQuat quaternionRotation = FQuat(rotation);

	Direction = quaternionRotation.RotateVector(forwardVector);

	FVector End = Origin + (Direction * RayLength);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Origin,
		End,
		ECC_GameTraceChannel6
	);

	Hit = bHit;
	
	DrawDebugLine(
		GetWorld(),
		Origin,
		End,
		FColor::Red,
		false,
		AIConfig->HideSpotFinderDebugLineLifeTime,
		0,                  
		AIConfig->HideSpotFinderDebugLineThickness
	);
	

	return HitResult;
}

bool UHideSpotFinder::ThisRayIsNotHittingPlayer(FHitResult raycastHits) const {

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	return raycastHits.GetActor()!=PlayerPawn;
}

bool UHideSpotFinder::IsThisPointNotVisibleByPlayer(FVector CurrentPoint) const {
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	FVector Direction = PlayerPawn->GetActorLocation() - CurrentPoint;

	float Distance = Direction.Length();
	Direction.Normalize();

	FVector Origin = CurrentPoint;

	FVector End = Origin + (Direction * Distance);

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Origin,
		End,
		ECC_Visibility
	);

	if (!bHit || (bHit && HitResult.GetActor() == PlayerPawn)) {
		return false;
	}

	return true;
}

bool UHideSpotFinder::IsThisPointOutsideColliders(FVector CurrentPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent) const {
	const FTransform ComponentTransform = ImpactedComponent->GetComponentTransform();

	const FBoxSphereBounds ComponentBounds = ImpactedComponent->CalcBounds(ComponentTransform);
	const FBox& BoundingBox = ComponentBounds.GetBox();

	return !BoundingBox.IsInside(CurrentPoint);
}

TOptional<FVector> UHideSpotFinder::GetClosestHidingSpot() {

	float currentAngle = 0.f;
	TOptional<FVector> PossibleHideSpot;
	TArray<FVector> possibleHideSpots;

	do
	{
		FVector Origin;
		FVector Direction;
		bool Hit;

		FHitResult raycastHits = MakeRaycastInSelectedAngle(currentAngle, AIConfig->RayLengthToFindObstacle, Origin, Direction, Hit);

		if (Hit && ThisRayIsNotHittingPlayer(raycastHits))
		{
			FindingPossiblePositionsAlongCurrentRay(raycastHits.ImpactPoint, raycastHits.Component, Direction, possibleHideSpots);
		}

		currentAngle += AIConfig->AngleRotationChecksToDetectHidingSpot;
	} while (currentAngle < 360.f);

	if (possibleHideSpots.Num() > 0)
	{
		SortPointsByDistance(possibleHideSpots);

		return possibleHideSpots[0];
	}

	return PossibleHideSpot;
}

void UHideSpotFinder::SortPointsByDistance(TArray<FVector>& PointsArray) {

	FVector ActorLocation = Enemy->GetActorLocation();

	auto DistanceToActor = [ActorLocation](const FVector& Point)
	{
		return FVector::DistSquared(ActorLocation, Point); 
	};

	Algo::Sort(PointsArray, [DistanceToActor](const FVector& A, const FVector& B)
		{
			return DistanceToActor(A) < DistanceToActor(B);
		});
}