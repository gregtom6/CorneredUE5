// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Interactor.h"
#include <CorneredPlayerController.h>
#include <Kismet/GameplayStatics.h>
#include "Interactable.h"
#include "InteractableDetector.h"
#include "Holdable.h"

// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	InteractableDetectorComp = Cast<UInteractableDetector>(GetOwner()->GetComponentByClass(UInteractableDetector::StaticClass()));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ACorneredPlayerController* CustomPlayerController = Cast<ACorneredPlayerController>(PlayerController);
		if (CustomPlayerController)
		{
			CustomPlayerController->InteractStartedInstance.AddUniqueDynamic(this, &UInteractor::InteractStarted);
			CustomPlayerController->InteractHappenedInstance.AddUniqueDynamic(this, &UInteractor::InteractHappened);
		}
	}
}


// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bInteractHappenedInThisFrame) {
		bInteractHappenedInThisFrame = false;
	}

	if (!Holdable) {
		return;
	}

	if (InteractableDetectorComp && !InteractableDetectorComp->ItWasValidHit()) {
		Holdable->HoldingFinished();
		Holdable = nullptr;
	}
}

void UInteractor::InteractStarted() {
	if (InteractableDetectorComp && InteractableDetectorComp->ItWasValidHit()) {
		FHitResult HitResult = InteractableDetectorComp->GetHitResult();
		AActor* HitActor = HitResult.GetActor();

		if (HitActor) {

			IInteractable* Pickable = Cast<IInteractable>(HitActor);
			if (Pickable) {
				Pickable->Interact();
				bInteractHappenedInThisFrame = true;
			}

			Holdable = Cast<IHoldable>(HitActor);

			if (Holdable) {
				Holdable->HoldingStarted();
			}
		}
	}
}

void UInteractor::InteractHappened() {
	if (InteractableDetectorComp && InteractableDetectorComp->ItWasValidHit()) {
		FHitResult HitResult = InteractableDetectorComp->GetHitResult();
		AActor* HitActor = HitResult.GetActor();

		if (HitActor) {

			Holdable = Cast<IHoldable>(HitActor);

			if (Holdable) {
				Holdable->HoldingFinished();
			}
		}
	}
}