// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "HideSpotFinder.h"
#include "Config_AI.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Algo/Sort.h"
#include "CharacterSpawner.h"
#include "EnemyCharacter.h"

// Sets default values for this component's properties
UHideSpotFinder::UHideSpotFinder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
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


// Called every frame
void UHideSpotFinder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHideSpotFinder::SortHitsBasedOnDistance() {

}

void UHideSpotFinder::FindingPossiblePositionsAlongCurrentRay(FVector Origin, FVector Direction, TArray<FVector>& possibleHideSpots, TArray<FHitResult> raycastHits, float rayLength) {
	float currentDistanceToCheckOnRay = 0.f;
	float stepCount = 1.f;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	do
	{
		currentDistanceToCheckOnRay = AIConfig->RayTraverseStepSizeToDiscoverHidingPlace * stepCount;

		if (currentDistanceToCheckOnRay > rayLength)
		{
			continue;
		}

		FVector currentPoint = Origin + (Direction * currentDistanceToCheckOnRay);

		FVector extent = FVector(AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance);

		FNavLocation ClosestNavmeshPoint;

		if (IsThisPointOutsideColliders(currentPoint) && IsThisPointNotVisibleByPlayer(currentPoint) && NavSystem->ProjectPointToNavigation(currentPoint, ClosestNavmeshPoint, extent))
		{
			possibleHideSpots.Add(ClosestNavmeshPoint.Location);
			break;
		}
		else
		{
			stepCount += 1.f;
		}
	} while (currentDistanceToCheckOnRay < rayLength);
}

TArray<FHitResult> UHideSpotFinder::MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction) {

	FVector End = Origin + (Direction * RayLength);

	TArray<FHitResult> HitResult;

	bool bHit = GetWorld()->LineTraceMultiByChannel(
		HitResult,
		Origin,
		End,
		ECC_Visibility
	);

	return HitResult;
}

bool UHideSpotFinder::ThisRayIsNotHittingPlayer(TArray<FHitResult> raycastHits) {

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	for (int i = 0; i < raycastHits.Num(); i++) {
		if (raycastHits[i].GetActor() == PlayerPawn) {
			return false;
		}
	}

	return true;
}

bool UHideSpotFinder::IsThisPointNotVisibleByPlayer(FVector CurrentPoint) {
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
		return true;
	}

	return false;
}

bool UHideSpotFinder::IsThisPointOutsideColliders(FVector CurrentPoint) {
	return true;
}

TOptional<FVector> UHideSpotFinder::GetClosestHidingSpot() {
	float currentAngle = 0.f;
	float angleRotationChecks = 5.f;
	float rayLength = 30.f;

	TOptional<FVector> PossibleHideSpot;

	TArray<FVector> possibleHideSpots;

	do
	{
		FVector Origin;
		FVector Direction;

		TArray<FHitResult> raycastHits = MakeRaycastInSelectedAngle(currentAngle, rayLength, Origin, Direction);

		if (raycastHits.Num() > 0 && ThisRayIsNotHittingPlayer(raycastHits))
		{
			//SortHitsBasedOnDistance(raycastHits);

			FindingPossiblePositionsAlongCurrentRay(Origin, Direction, possibleHideSpots, raycastHits, rayLength);
		}

		currentAngle += angleRotationChecks;
	} while (currentAngle < 360.f);

	if (possibleHideSpots.Num() > 0)
	{
		SortPointsByDistance(possibleHideSpots);

		//m_MovementTargetPoint.position = possibleHideSpots[0];
		return possibleHideSpots[0];
	}

	return PossibleHideSpot;
}

void UHideSpotFinder::SortPointsByDistance(TArray<FVector>& PointsArray) {
	//possibleHideSpots.Sort((a, b) = > Vector3.Distance(a, m_EnemyTransform.position).CompareTo(Vector3.Distance(b, m_EnemyTransform.position)));

	FVector ActorLocation = Enemy->GetActorLocation();

	// Lambda function to calculate distance between two points
	auto DistanceToActor = [ActorLocation](const FVector& Point)
	{
		return FVector::DistSquared(ActorLocation, Point); // Use DistSquared to avoid sqrt for efficiency
	};

	// Sort the array using a lambda function as a comparator
	Algo::Sort(PointsArray, [DistanceToActor](const FVector& A, const FVector& B)
		{
			return DistanceToActor(A) < DistanceToActor(B);
		});
}