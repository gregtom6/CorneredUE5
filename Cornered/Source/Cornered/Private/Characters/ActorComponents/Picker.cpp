// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/Picker.h"
#include "Characters/ActorComponents/InteractableDetector.h"
#include <Kismet/GameplayStatics.h>
#include "System/CorneredPlayerController.h"
#include "Items/Pickable.h"

UPicker::UPicker()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPicker::BeginPlay()
{
	Super::BeginPlay();

	InteractableDetectorComp = GetOwner()->FindComponentByClass<UInteractableDetector>();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ACorneredPlayerController* CustomPlayerController = Cast<ACorneredPlayerController>(PlayerController);
		if (CustomPlayerController)
		{
			CustomPlayerController->PickupHappenedInstance.AddUniqueDynamic(this, &UPicker::PickupHappened);
			CustomPlayerController->DropHappenedInstance.AddUniqueDynamic(this, &UPicker::DropHappened);
		}
	}
}

void UPicker::PickupHappened() {
	if (!bPickupDropHappenedInThisFrame && !PickedPickable && InteractableDetectorComp && InteractableDetectorComp->ItWasValidHit()) {
		FHitResult HitResult = InteractableDetectorComp->GetHitResult();
		AActor* HitActor = HitResult.GetActor();

		if (HitActor) {

			IPickable* Pickable = Cast<IPickable>(HitActor);
			if (Pickable) {
				Pickable->Pickup(GetOwner());
				PickedPickable = TScriptInterface<IPickable>(Cast<UObject>(HitActor));
				bPickupDropHappenedInThisFrame = true;
			}
		}
	}
}

void UPicker::DropHappened() {
	if (!bPickupDropHappenedInThisFrame && PickedPickable && PickedPickable->IsPicked())
	{
		PickedPickable->Drop();
		PickedPickable = nullptr;
		bPickupDropHappenedInThisFrame = true;
	}
}

void UPicker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bPickupDropHappenedInThisFrame = false;
}

IPickable* UPicker::GetPickedPickable() const {
	if (PickedPickable.GetObject()) {
		return Cast<IPickable>(PickedPickable.GetObject());
	}

	return nullptr;
}

void UPicker::RemovePickable() {
	PickedPickable = nullptr;
}