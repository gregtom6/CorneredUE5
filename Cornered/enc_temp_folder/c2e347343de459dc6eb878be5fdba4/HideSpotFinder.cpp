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
#include "NavigationSystem.h"

UHideSpotFinder::UHideSpotFinder()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHideSpotFinder::BeginPlay()
{
	Super::BeginPlay();

	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	bCanLookForNewHidingSpot = true;

	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->OnEnemyGenerated.AddUniqueDynamic(this, &UHideSpotFinder::OnEnemyGenerated);
	}
}

void UHideSpotFinder::ManageDebugDrawings(bool enabled) {
	bDrawDebug = enabled;
}

void UHideSpotFinder::RegisterCallback(FHideSpotSearchingEnded hideSpotSearchingEnded) {
	HideSpotSearchingEnded = hideSpotSearchingEnded;
}

void UHideSpotFinder::OnEnemyGenerated(AEnemyCharacter* EnemyCharacter) {
	Enemy = EnemyCharacter;
}

void UHideSpotFinder::FindingPossibleHideSpotAlongCurrentRayAsync(FVector ImpactPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent, FVector Direction, int foundInIndex, float CurrentlyCheckedAngle, AActor* Obstacle) {

	TRACE_CPUPROFILER_EVENT_SCOPE_STR("HideSpotFinder_FindingPossiblePositionsAlongCurrentRay");

	float currentDistanceToCheckOnRay = 0.f;
	stepCount = AIConfig->ObstacleFindingRayStartingStepCount;

	testInteger = 0;

	do
	{
		TRACE_CPUPROFILER_EVENT_SCOPE_STR("HideSpotFinder_Check"); //38.7 ms

		if (IsPossibleHideSpotFoundInThisAngle(Obstacle, CurrentlyCheckedAngle)) {
			return;
		}

		currentDistanceToCheckOnRay = AIConfig->RayTraverseStepSizeToDiscoverHidingPlace * stepCount;

		if (currentDistanceToCheckOnRay >= AIConfig->ObstacleFindingRayMaxDistance / 2.f)
		{
			return;
		}

		FVector currentPoint = ImpactPoint + (Direction * currentDistanceToCheckOnRay);

		FVector extent = FVector(AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance);

		FNavLocation ClosestNavmeshPoint;

		bool isCurrentPointProjectableToNavmesh = NavSystem->ProjectPointToNavigation(currentPoint, ClosestNavmeshPoint, extent);

		FNavLocation ClosestActorLocationPointOnNavmesh;

		bool isAILocationProjectableToNavmesh = NavSystem->ProjectPointToNavigation(GetOwner()->GetActorLocation(), ClosestActorLocationPointOnNavmesh, extent);

		if (FMath::IsNearlyEqual(currentPoint.X,ClosestNavmeshPoint.Location.X) && FMath::IsNearlyEqual(currentPoint.Y,ClosestNavmeshPoint.Location.Y) && IsThisPointOutsideColliders(ClosestNavmeshPoint.Location, ImpactedComponent) && IsThisPointNotVisibleByPlayer(ClosestNavmeshPoint.Location) && isCurrentPointProjectableToNavmesh && isAILocationProjectableToNavmesh) {
			const FNavAgentProperties& NavAgentProperties = Cast<AEnemyCharacter>(GetOwner())->GetNavAgentPropertiesRef();

			FPathFindingQuery Query;
			Query.StartLocation = ClosestActorLocationPointOnNavmesh.Location;
			Query.EndLocation = ClosestNavmeshPoint.Location;
			Query.NavAgentProperties = NavAgentProperties;
			Query.NavData = NavSystem->GetDefaultNavDataInstance(FNavigationSystem::Create);
			Query.QueryFilter = Query.NavData->GetDefaultQueryFilter();
			Query.PathInstanceToFill = MakeShareable(new FNavigationPath());

			uint32 PathRequestID = NavSystem->FindPathAsync(NavAgentProperties, Query, FNavPathQueryDelegate::CreateUObject(this, &UHideSpotFinder::OnPathFound), EPathFindingMode::Regular);

			int position = GetLocationOfAngleHideouts(foundInIndex, CurrentlyCheckedAngle);

			obstacleCheckDetails[foundInIndex].AnglesAndPossibleHideSpots[position].PathRequestIDs.Add(PathRequestID);

			testInteger += 1;
		}

		stepCount += AIConfig->ObstacleFindingRayDeltaStepSize;

	} while (currentDistanceToCheckOnRay < AIConfig->ObstacleFindingRayMaxDistance / 2.f);
}

bool UHideSpotFinder::IsPossibleHideSpotFoundInThisAngle(AActor* Obstacle, float CurrentlyCheckedAngle) {
	for (int i = 0; i < obstacleCheckDetails.Num(); i++) {
		if (obstacleCheckDetails[i].ObstacleActor == Obstacle) {
			for (int j = 0; j < obstacleCheckDetails[i].AnglesAndPossibleHideSpots.Num(); j++) {
				if (obstacleCheckDetails[i].AnglesAndPossibleHideSpots[j].Angle == CurrentlyCheckedAngle && obstacleCheckDetails[i].AnglesAndPossibleHideSpots[j].PossibleHideSpot.IsSet()) {
					return true;
				}
			}
		}
	}

	return false;
}

void UHideSpotFinder::OnPathFound(uint32 PathRequestID, ENavigationQueryResult::Type Result, FNavPathSharedPtr Path) {

	int location = -1;

	testInteger -= 1;

	if (GetBackObstacleDetailsWherePathRequestID(PathRequestID, location)) {

		float Angle = GetBackAngleOfPathRequestID(obstacleCheckDetails[location].ObstacleActor, PathRequestID);
		int position = GetLocationOfAngleHideouts(location, Angle);

		if (!IsPossibleHideSpotSetted(location, position) && Result == ENavigationQueryResult::Type::Success && Path && Path->IsValid() && Path->GetPathPoints().Num() > 1)
		{
			obstacleCheckDetails[location].AnglesAndPossibleHideSpots[position].PossibleHideSpot = Path->GetPathPoints().Last();
		}

		if (AreAllPossibleHideSpotsSetted(location) && currentlyCheckedAngle >= 360.f) {
			ProcessingPossibleHideSpots();
		}
	}
}

bool UHideSpotFinder::IsPossibleHideSpotSetted(int location, int position) {
	return obstacleCheckDetails[location].AnglesAndPossibleHideSpots[position].PossibleHideSpot.IsSet();
}

bool UHideSpotFinder::AreAllPossibleHideSpotsSetted(int location) {
	for (int i = 0; i < obstacleCheckDetails[location].AnglesAndPossibleHideSpots.Num(); i++) {
		if (!obstacleCheckDetails[location].AnglesAndPossibleHideSpots[i].PossibleHideSpot.IsSet()) {
			return false;
		}
	}
	return true;
}

int UHideSpotFinder::GetLocationOfAngleHideouts(int location, float CurrentAngle) {
	for (int i = 0; i < obstacleCheckDetails[location].AnglesAndPossibleHideSpots.Num(); i++) {
		if (obstacleCheckDetails[location].AnglesAndPossibleHideSpots[i].Angle == CurrentAngle) {
			return i;
		}
	}

	return -1;
}

float UHideSpotFinder::GetBackAngleOfPathRequestID(AActor* Obstacle, uint32 PathRequestID) {
	for (int i = 0; i < obstacleCheckDetails.Num(); i++) {
		if (obstacleCheckDetails[i].ObstacleActor == Obstacle) {
			for (int j = 0; j < obstacleCheckDetails[i].AnglesAndPossibleHideSpots.Num(); j++) {
				if (obstacleCheckDetails[i].AnglesAndPossibleHideSpots[j].PathRequestIDs.Contains(PathRequestID)) {
					return obstacleCheckDetails[i].AnglesAndPossibleHideSpots[j].Angle;
				}
			}
		}
	}
	return -1.f;
}

bool UHideSpotFinder::GetBackObstacleDetailsWherePathRequestID(uint32 PathRequestID, int& location) {
	for (int i = 0; i < obstacleCheckDetails.Num(); i++) {
		for (int j = 0; j < obstacleCheckDetails[i].AnglesAndPossibleHideSpots.Num(); j++) {
			if (obstacleCheckDetails[i].AnglesAndPossibleHideSpots[j].PathRequestIDs.Contains(PathRequestID)) {
				location = i;
				return true;
			}

		}
	}

	return false;
}

FHitResult UHideSpotFinder::MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit) const {

	TRACE_CPUPROFILER_EVENT_SCOPE_STR("HideSpotFinder_MakeRaycastInSelectedAngle");

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

	DrawDebugLines(Origin, End);

	return HitResult;
}

void UHideSpotFinder::DrawDebugLines(FVector Origin, FVector End) const {

	if (!bDrawDebug) {
		return;
	}

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
}

bool UHideSpotFinder::ThisRayIsNotHittingPlayer(FHitResult raycastHits) const {

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	return raycastHits.GetActor() != PlayerPawn;
}

bool UHideSpotFinder::IsThisPointNotVisibleByPlayer(FVector CurrentPoint) const {

	TRACE_CPUPROFILER_EVENT_SCOPE_STR("HideSpotFinder_IsThisPointNotVisibleByPlayer");

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

	TRACE_CPUPROFILER_EVENT_SCOPE_STR("HideSpotFinder_IsThisPointOutsideColliders");

	const FTransform ComponentTransform = ImpactedComponent->GetComponentTransform();

	const FBoxSphereBounds ComponentBounds = ImpactedComponent->CalcBounds(ComponentTransform);
	const FBox& BoundingBox = ComponentBounds.GetBox();

	return !BoundingBox.IsInside(CurrentPoint);
}

void UHideSpotFinder::GetClosestHidingSpotAsync() {

	TRACE_CPUPROFILER_EVENT_SCOPE_STR("HideSpotFinder_GetClosestHidingSpot");

	if (!bCanLookForNewHidingSpot) {
		return;
	}

	bCanLookForNewHidingSpot = false;

	currentlyCheckedAngle = 0.f;

	obstacleCheckDetails.Empty();
	bDidFindPossibleHideSpotAlongThisRay = false;
	stepCount = 0.f;

	do
	{
		FVector Origin;
		FVector Direction;
		bool Hit;

		FHitResult raycastHits = MakeRaycastInSelectedAngle(currentlyCheckedAngle, AIConfig->RayLengthToFindObstacle, Origin, Direction, Hit);

		if (DidIFindObstacle(Hit, raycastHits))
		{
			int foundInIndex = LoadObstacleDetailsIfExists(raycastHits);

			StoreGeneralObstacleDetails(raycastHits, currentlyCheckedAngle, foundInIndex);

			FindingPossibleHideSpotAlongCurrentRayAsync(raycastHits.ImpactPoint, raycastHits.Component, Direction, foundInIndex, currentlyCheckedAngle, raycastHits.GetActor());
		}

		currentlyCheckedAngle += AIConfig->AngleRotationChecksToDetectHidingSpot;
	} while (currentlyCheckedAngle < 360.f);
}

void UHideSpotFinder::StoreGeneralObstacleDetails(FHitResult raycastHits, float CurrentAngle, int foundInIndex) {

	obstacleCheckDetails[foundInIndex].ObstacleActor = raycastHits.GetActor();

	FAngleAndItsPossibleHideSpot AngleAndItsPossibleHideSpot;
	AngleAndItsPossibleHideSpot.Angle = CurrentAngle;
	obstacleCheckDetails[foundInIndex].AnglesAndPossibleHideSpots.Add(AngleAndItsPossibleHideSpot);
}

void UHideSpotFinder::ProcessingPossibleHideSpots() {

	TOptional<FVector> FinalSelectedHideSpot;

	if (AreTherePossibleHideSpots(obstacleCheckDetails))
	{
		SetBestHideSpotsForAllObstacles(obstacleCheckDetails);

		TArray<FVector> bestHideSpots = GetBestHideSpots(obstacleCheckDetails);

		SortPointsByDistance(bestHideSpots);

		FinalSelectedHideSpot = bestHideSpots[0];

		DrawDebug(FinalSelectedHideSpot.GetValue());
	}

	if (HideSpotSearchingEnded.IsBound()) {
		HideSpotSearchingEnded.Broadcast(FinalSelectedHideSpot.GetValue(), true);
		bCanLookForNewHidingSpot = true;
	}
}

void UHideSpotFinder::DrawDebug(FVector FinalSelectedHideSpot) {

	if (!bDrawDebug) {
		return;
	}

	for (int i = 0; i < obstacleCheckDetails.Num(); i++) {
		for (int j = 0; j < obstacleCheckDetails[i].AnglesAndPossibleHideSpots.Num(); j++) {
			DrawDebugSphere(GetWorld(), obstacleCheckDetails[i].AnglesAndPossibleHideSpots[j].PossibleHideSpot.GetValue(), AIConfig->HideSpotDebugSphereRadius / 2.f, AIConfig->HideSpotDebugSphereSegments / 2.f, FColor::Green, false, 0.5f, 0, AIConfig->HideSpotDebugSphereThickness);
		}
	}
	DrawDebugSphere(GetWorld(), FinalSelectedHideSpot, AIConfig->HideSpotDebugSphereRadius, AIConfig->HideSpotDebugSphereSegments, FColor::Red, false, -1.f, 0, AIConfig->HideSpotDebugSphereThickness);
}

int UHideSpotFinder::LoadObstacleDetailsIfExists(FHitResult raycastHits) {

	int foundInIndex = -1;

	if (!IsObstacleAlreadyFoundInPreviousAngle(raycastHits.GetActor(), obstacleCheckDetails, foundInIndex)) {

		obstacleCheckDetails.Add(FObstacleHideSpots());
		foundInIndex = obstacleCheckDetails.Num() - 1;
	}

	return foundInIndex;
}

bool UHideSpotFinder::AreTherePossibleHideSpots(TArray<FObstacleHideSpots> possibleHideSpots) const {
	return possibleHideSpots.Num() > 0;
}

bool UHideSpotFinder::DidIFindObstacle(bool Hit, FHitResult raycastHits) const {
	return Hit && ThisRayIsNotHittingPlayer(raycastHits);
}

TArray<FVector> UHideSpotFinder::GetBestHideSpots(TArray<FObstacleHideSpots> obstacles) const {
	TArray<FVector> highlightedHideSpots;

	for (int i = 0; i < obstacles.Num(); i++) {
		highlightedHideSpots.Add(obstacles[i].BestHideSpot);
	}

	return highlightedHideSpots;
}

void UHideSpotFinder::SetBestHideSpotsForAllObstacles(TArray<FObstacleHideSpots>& obstacles) {

	TRACE_CPUPROFILER_EVENT_SCOPE_STR("HideSpotFinder_FillHighlightedHideSpots");

	for (int i = 0; i < obstacles.Num(); i++) {

		if (obstacles[i].AnglesAndPossibleHideSpots.Num() > 0) {

			TArray<float> NormalizedAngles;

			for (int j = 0; j < obstacles[i].AnglesAndPossibleHideSpots.Num(); j++) {
				NormalizedAngles.Add(NormalizeAngle(obstacles[i].AnglesAndPossibleHideSpots[j].Angle));
			}

			float MeanAngle = CalculateCircularMean(NormalizedAngles);

			int closestAngleIndex = GetClosestIndex(NormalizedAngles, MeanAngle);

			if (closestAngleIndex >= 0 && closestAngleIndex < obstacles[i].AnglesAndPossibleHideSpots.Num()) {
				FAngleAndItsPossibleHideSpot middleElement = obstacles[i].AnglesAndPossibleHideSpots[closestAngleIndex];
				obstacles[i].BestHideSpot = middleElement.PossibleHideSpot.GetValue();
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

bool UHideSpotFinder::IsObstacleAlreadyFoundInPreviousAngle(AActor* ObstacleActor, TArray<FObstacleHideSpots> obstacles, int& foundInIndex) const {
	for (int i = 0; i < obstacles.Num(); i++) {
		if (obstacles[i].ObstacleActor == ObstacleActor) {
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