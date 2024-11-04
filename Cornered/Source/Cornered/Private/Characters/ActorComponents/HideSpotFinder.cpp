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
		MySubsystem->OnEnemyGenerated.AddUniqueDynamic(this, &UHideSpotFinder::OnEnemyGenerated);
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

		FNavLocation ClosestActorLocationPointOnNavmesh;

		bool navQuest2 = NavSystem->ProjectPointToNavigation(GetOwner()->GetActorLocation(), ClosestActorLocationPointOnNavmesh, extent);

		UNavigationPath* NavPath = NavSystem->FindPathToLocationSynchronously(GetWorld(), ClosestActorLocationPointOnNavmesh.Location, ClosestNavmeshPoint.Location);

		if (IsThisPointOutsideColliders(ClosestNavmeshPoint.Location, ImpactedComponent) && IsThisPointNotVisibleByPlayer(ClosestNavmeshPoint.Location) && navQuest && navQuest2 && NavPath && NavPath->IsValid() && NavPath->PathPoints.Num() > 1)
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

	return raycastHits.GetActor() != PlayerPawn;
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
	TOptional<FVector> SelectedHideSpot;
	TArray<FObstacleHideSpots> possibleHideSpots;

	do
	{
		FVector Origin;
		FVector Direction;
		bool Hit;

		FHitResult raycastHits = MakeRaycastInSelectedAngle(currentAngle, AIConfig->RayLengthToFindObstacle, Origin, Direction, Hit);

		if (Hit && ThisRayIsNotHittingPlayer(raycastHits))
		{
			FObstacleHideSpots loadedObstacleDetails;
			int foundInIndex = -1;
			if (IsObstacleAlreadyFound(raycastHits.GetActor(), possibleHideSpots, loadedObstacleDetails, foundInIndex)) {
				FindingPossiblePositionsAlongCurrentRay(raycastHits.ImpactPoint, raycastHits.Component, Direction, loadedObstacleDetails.PossibleHideSpots);
				loadedObstacleDetails.Angles.Add(currentAngle);
				possibleHideSpots[foundInIndex] = loadedObstacleDetails;
			}
			else {
				FindingPossiblePositionsAlongCurrentRay(raycastHits.ImpactPoint, raycastHits.Component, Direction, loadedObstacleDetails.PossibleHideSpots);
				loadedObstacleDetails.ObstacleActor = raycastHits.GetActor();
				loadedObstacleDetails.Angles.Add(currentAngle);
				possibleHideSpots.Add(loadedObstacleDetails);
			}
		}

		currentAngle += AIConfig->AngleRotationChecksToDetectHidingSpot;
	} while (currentAngle < 360.f);

	if (possibleHideSpots.Num() > 0)
	{
		FillHighlightedHideSpots(possibleHideSpots);

		TArray<FVector> highlightedHideSpots = GetHighlightedHideSpots(possibleHideSpots);

		SortPointsByDistance(highlightedHideSpots);

		SelectedHideSpot = highlightedHideSpots[0];
	}
	
	return SelectedHideSpot;
}

TArray<FVector> UHideSpotFinder::GetHighlightedHideSpots(TArray<FObstacleHideSpots> obstacles) const {
	TArray<FVector> highlightedHideSpots;

	for (int i = 0; i < obstacles.Num(); i++) {
		highlightedHideSpots.Add(obstacles[i].HighlightedHideSpot);
	}

	return highlightedHideSpots;
}

void UHideSpotFinder::FillHighlightedHideSpots(TArray<FObstacleHideSpots>& obstacles) {
	for (int i = 0; i < obstacles.Num(); i++) {
		if (obstacles[i].PossibleHideSpots.Num() > 0) {

			TArray<float> NormalizedAngles;

			for (int j = 0; j < obstacles[i].Angles.Num(); j++) {
				NormalizedAngles.Add(NormalizeAngle(obstacles[i].Angles[j]));
			}

			float MeanAngle = CalculateCircularMean(NormalizedAngles);

			int closestAngleIndex = GetClosestIndex(NormalizedAngles, MeanAngle);

			if (closestAngleIndex >= 0) {
				FVector middleElement = obstacles[i].PossibleHideSpots[closestAngleIndex];
				obstacles[i].HighlightedHideSpot = middleElement;
			}
		}
	}
}

float UHideSpotFinder::CalculateCircularMean(const TArray<float>& Angles) const {
	float sumSin = 0.0f;
	float sumCos = 0.0f;

	for (float Angle : Angles) {
		float Radians = FMath::DegreesToRadians(Angle);
		sumSin += FMath::Sin(Radians);
		sumCos += FMath::Cos(Radians);
	}

	float meanRadians = FMath::Atan2(sumSin, sumCos);

	float meanDegrees = FMath::RadiansToDegrees(meanRadians);
	return NormalizeAngle(meanDegrees);
}

float UHideSpotFinder::NormalizeAngle(float Angle) const {
	while (Angle >= 360.0f) Angle -= 360.0f;
	while (Angle < 0.0f) Angle += 360.0f;
	return Angle;
}

int UHideSpotFinder::GetClosestIndex(const TArray<float>& Array, float TargetValue) const
{
	if (Array.Num() == 0)
	{
		return -1;
	}

	int ClosestIndex = 0;
	float ClosestDistance = FMath::Abs(Array[0] - TargetValue);

	for (int i = 1; i < Array.Num(); ++i)
	{
		float CurrentDistance = FMath::Abs(Array[i] - TargetValue);
		if (CurrentDistance < ClosestDistance)
		{
			ClosestDistance = CurrentDistance;
			ClosestIndex = i;
		}
	}

	return ClosestIndex;
}

bool UHideSpotFinder::IsObstacleAlreadyFound(AActor* ObstacleActor, TArray<FObstacleHideSpots> obstacles, FObstacleHideSpots& loadedObstacleDetails, int& foundInIndex) const {
	for (int i = 0; i < obstacles.Num(); i++) {
		if (obstacles[i].ObstacleActor == ObstacleActor) {
			loadedObstacleDetails = obstacles[i];
			foundInIndex = i;
			return true;
		}
	}

	return false;
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