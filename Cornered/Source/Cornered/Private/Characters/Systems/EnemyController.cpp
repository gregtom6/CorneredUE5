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

	MoveToLocation(ClosestNavmeshPoint);
}

void AEnemyController::HideFromPlayer() {

	UHideSpotFinder* hideSpotFinder = GetPawn()->FindComponentByClass<UHideSpotFinder>();

	TOptional<FVector> closestHidingSpot = hideSpotFinder->GetClosestHidingSpot();

	if (closestHidingSpot.IsSet()) {
		MoveToLocation(closestHidingSpot.GetValue());
		DrawDebugSphere(GetWorld(), closestHidingSpot.GetValue(), AIConfig->HideSpotDebugSphereRadius, AIConfig->HideSpotDebugSphereSegments, FColor::Red, false, -1.f, 0, AIConfig->HideSpotDebugSphereThickness);
	}
}

EMovementState AEnemyController::GetMovementState() const {
	return MovementState;
}