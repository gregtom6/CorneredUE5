// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/EnemyController.h"
#include "System/CorneredGameMode.h"
#include "Navigation/PathFollowingComponent.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Components/StateTreeComponent.h"
#include "Characters/ActorComponents/HideSpotFinder.h"
#include "DrawDebugHelpers.h"
#include "Configs/DataAssets/Config_AI.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

AEnemyController::AEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	CorneredGameMode->TimeOverHappened.AddUniqueDynamic(this, &AEnemyController::OnTimerOverHappened);
}

void AEnemyController::OnTimerOverHappened() {
	bIsTimerOver = true;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());

	EnemyCharacter->StateTreeComp->StartLogic();
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UPathFollowingComponent* PathFollowingComp = GetPathFollowingComponent()) {
		MovementState = PathFollowingComp->GetStatus() == EPathFollowingStatus::Moving ? EMovementState::Walking : EMovementState::Standing;
	}
}


void AEnemyController::FollowPlayer() {
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	FVector extent = FVector(AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance, AIConfig->NavmeshSamplePositionDistance);

	FNavLocation ClosestNavmeshPoint;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	NavSystem->ProjectPointToNavigation(PlayerPawn->GetActorLocation(), ClosestNavmeshPoint, extent);

	MoveToLocation(ClosestNavmeshPoint, -1.0f, false);
}

void AEnemyController::HideFromPlayer() {

	UHideSpotFinder* hideSpotFinder = GetPawn()->FindComponentByClass<UHideSpotFinder>();

	TOptional<FVector> closestHidingSpot = hideSpotFinder->GetClosestHidingSpot();

	if (closestHidingSpot.IsSet()) {
		MoveToLocation(closestHidingSpot.GetValue(), -1.0f, false);
		DrawDebugSphere(GetWorld(), closestHidingSpot.GetValue(), AIConfig->HideSpotDebugSphereRadius, AIConfig->HideSpotDebugSphereSegments, FColor::Red, false, -1.f, 0, AIConfig->HideSpotDebugSphereThickness);
	}
}

EMovementState AEnemyController::GetMovementState() const {
	return MovementState;
}

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.Code == EPathFollowingResult::Success)
	{
		UE_LOG(LogTemp, Log, TEXT("Agent successfully reached the destination."));
	}
	else if (Result.Code == EPathFollowingResult::Blocked)
	{
		UE_LOG(LogTemp, Warning, TEXT("Agent's path is blocked."));
	}
	else if (Result.Code == EPathFollowingResult::Invalid)
	{
		UE_LOG(LogTemp, Warning, TEXT("Agent could not find a valid path to the destination."));
	}
	else if (Result.Code == EPathFollowingResult::OffPath)
	{
		UE_LOG(LogTemp, Warning, TEXT("Agent went off path."));
	}

	UHideSpotFinder* hideSpotFinder = GetPawn()->FindComponentByClass<UHideSpotFinder>();

	TOptional<FVector> closestHidingSpot = hideSpotFinder->GetClosestHidingSpot();

	if (closestHidingSpot.IsSet()) {
		float DistanceToGoal = FVector::Dist(GetPawn()->GetNavAgentLocation(), closestHidingSpot.GetValue());
	
		UE_LOG(LogTemp, Warning, TEXT("Distance to goal: %f"), DistanceToGoal);
	}
}