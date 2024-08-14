// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyController.h"
#include "CorneredGameMode.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnemyCharacter.h"
#include "Components/StateTreeComponent.h"
#include "HideSpotFinder.h"

AEnemyController::AEnemyController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
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

	/*

	if (!bIsTimerOver) {
		return;
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	if (UPathFollowingComponent* PathFollowingComp = GetPathFollowingComponent()) {

		MovementState = PathFollowingComp->GetStatus() == EPathFollowingStatus::Moving ? EMovementState::Walking : EMovementState::Standing;

		if (PathFollowingComp->GetStatus() != EPathFollowingStatus::Moving && FVector::Distance(PlayerPawn->GetActorLocation(), GetPawn()->GetActorLocation()) > 100.f) {
			FollowPlayer();
		}
	}
	*/
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
	}
}

EMovementState AEnemyController::GetMovementState() const {
	return MovementState;
}