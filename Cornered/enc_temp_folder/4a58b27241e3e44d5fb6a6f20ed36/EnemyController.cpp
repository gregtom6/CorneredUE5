// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyController.h"
#include "CorneredGameMode.h"
#include "Navigation/PathFollowingComponent.h"

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

	if (UPathFollowingComponent* PathFollowingComp = GetPathFollowingComponent()) {

		PathFollowingComp->OnRequestFinished.AddUObject(this, &AEnemyController::OnMoveCompleted);
	}
}

void AEnemyController::OnTimerOverHappened() {
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();
	MoveToActor(PlayerPawn);
}

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {

	
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();


	if (UPathFollowingComponent* PathFollowingComp = GetPathFollowingComponent()) {


		if (PathFollowingComp->GetStatus() != EPathFollowingStatus::Moving && FVector::Distance(PlayerPawn->GetActorLocation(), GetPawn()->GetActorLocation()) > 100.f) {
			OnTimerOverHappened();
		}

	}
}
