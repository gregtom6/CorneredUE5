// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "HideSpotFinder.h"
#include "Config_AI.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Algo/Sort.h"
#include "CharacterSpawner.h"
#include "EnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"

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

void UHideSpotFinder::FindingPossiblePositionsAlongCurrentRay(FVector ImpactPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent, FVector Direction, TArray<FVector>& possibleHideSpots) {
	float currentDistanceToCheckOnRay = 0.f;
	float stepCount = 5.f;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	do
	{
		currentDistanceToCheckOnRay = AIConfig->RayTraverseStepSizeToDiscoverHidingPlace * stepCount;

		if (currentDistanceToCheckOnRay >= 5000.f)
		{
			continue;
		}

		FVector currentPoint = ImpactPoint + (Direction * currentDistanceToCheckOnRay);

		FVector extent = FVector(AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance);

		FNavLocation ClosestNavmeshPoint;

		bool navQuest = NavSystem->ProjectPointToNavigation(currentPoint, ClosestNavmeshPoint, extent);

		if (navQuest) {

		}

		if (IsThisPointOutsideColliders(currentPoint, ImpactedComponent) && IsThisPointNotVisibleByPlayer(currentPoint) && navQuest)
		{
			possibleHideSpots.Add(ClosestNavmeshPoint.Location);
			break;
		}
		else
		{
			stepCount += 1.f;
		}
	} while (currentDistanceToCheckOnRay >= 5000.f);
}

FHitResult UHideSpotFinder::MakeRaycastInSelectedAngle(float CurrentAngle, float RayLength, FVector& Origin, FVector& Direction, bool& Hit) {

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(PlayerController->GetPawn());

	UCameraComponent* cameraComp = Cast<UCameraComponent>(PlayerPawn->GetComponentByClass(UCameraComponent::StaticClass()));

	Origin = cameraComp->GetComponentLocation() + FVector(0.f, 0.f, 100.f);

	FVector forwardVector = cameraComp->GetForwardVector();

	// Create a rotation around the Y-axis by currentAngle degrees
	FRotator rotation(0.0f, CurrentAngle, 0.0f);

	// Convert the FRotator to a quaternion for the rotation
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
		GetWorld(),         // World context (you can usually get this from an actor)
		Origin,      // Start location of the line
		End,        // End location of the line
		FColor::Red,          // Color of the line
		false,              // Whether the line should persist or not (false means it will disappear after lifeTime)
		0.001f,           // Time in seconds before the line disappears
		0,                  // Depth priority (0 is default)
		2.0f       // Thickness of the line
	);
	

	return HitResult;
}

bool UHideSpotFinder::ThisRayIsNotHittingPlayer(FHitResult raycastHits) {

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	return raycastHits.GetActor()!=PlayerPawn;
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

bool UHideSpotFinder::IsThisPointOutsideColliders(FVector CurrentPoint, TWeakObjectPtr<UPrimitiveComponent> ImpactedComponent) {
	const FTransform ComponentTransform = ImpactedComponent->GetComponentTransform();

	// Transform the point from world space to local space
	//FVector LocalPoint = ComponentTransform.InverseTransformPosition(WorldPoint);

	// Get the component's bounds
	const FBoxSphereBounds ComponentBounds = ImpactedComponent->CalcBounds(ComponentTransform);
	const FBox& BoundingBox = ComponentBounds.GetBox();

	// Check if the local point is within the bounding box
	return !BoundingBox.IsInside(CurrentPoint);
}

TOptional<FVector> UHideSpotFinder::GetClosestHidingSpot() {
	float currentAngle = 0.f;
	float angleRotationChecks = 15.f;
	float rayLength = 1500.f;

	TOptional<FVector> PossibleHideSpot;

	TArray<FVector> possibleHideSpots;

	do
	{
		FVector Origin;
		FVector Direction;
		bool Hit;

		FHitResult raycastHits = MakeRaycastInSelectedAngle(currentAngle, rayLength, Origin, Direction, Hit);

		if (Hit && ThisRayIsNotHittingPlayer(raycastHits))
		{
			//SortHitsBasedOnDistance(raycastHits);

			FindingPossiblePositionsAlongCurrentRay(raycastHits.ImpactPoint, raycastHits.Component, Direction, possibleHideSpots);
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