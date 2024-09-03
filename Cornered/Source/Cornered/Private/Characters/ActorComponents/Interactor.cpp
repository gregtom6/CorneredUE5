// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/Interactor.h"
#include "System/CorneredPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "Items/Interactable.h"
#include "Characters/ActorComponents/InteractableDetector.h"
#include "Environment/Interactables/Holdable.h"

UInteractor::UInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	InteractableDetectorComp = GetOwner()->FindComponentByClass<UInteractableDetector>();

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