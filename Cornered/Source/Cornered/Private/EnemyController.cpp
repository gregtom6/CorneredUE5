// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyController.h"
#include "CorneredGameMode.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnemyCharacter.h"
#include "Components/StateTreeComponent.h"
#include "HideSpotFinder.h"
#include "DrawDebugHelpers.h"
#include "Config_AI.h"

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
	MoveToActor(PlayerPawn);
}

void AEnemyController::HideFromPlayer() {
	UHideSpotFinder* hideSpotFinder = Cast<UHideSpotFinder>(GetPawn()->GetComponentByClass(UHideSpotFinder::StaticClass()));

	TOptional<FVector> closestHidingSpot = hideSpotFinder->GetClosestHidingSpot();

	if (closestHidingSpot.IsSet()) {
		MoveToLocation(closestHidingSpot.GetValue());
		DrawDebugSphere(GetWorld(), closestHidingSpot.GetValue(), 100.f, 12, FColor::Red, false, -1.f, 0, 1.0f);
	}
}

EMovementState AEnemyController::GetMovementState() const {
	return MovementState;
}