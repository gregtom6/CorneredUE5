// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/Picker.h"
#include "Characters/ActorComponents/InteractableDetector.h"
#include <Kismet/GameplayStatics.h>
#include "System/CorneredPlayerController.h"
#include "Items/IPickable.h"

// Sets default values for this component's properties
UPicker::UPicker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
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

			IIPickable* Pickable = Cast<IIPickable>(HitActor);
			if (Pickable) {
				Pickable->Pickup(GetOwner());
				PickedPickable = Pickable;
				bPickupDropHappenedInThisFrame = true;

				UE_LOG(LogTemp, Warning, TEXT("pickup"));
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

		UE_LOG(LogTemp, Warning, TEXT("drop"));
	}
}

void UPicker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bPickupDropHappenedInThisFrame) {
		bPickupDropHappenedInThisFrame = false;

		UE_LOG(LogTemp, Warning, TEXT("falsera"));
	}
}

IIPickable* UPicker::GetPickedPickable() const {
	return PickedPickable;
}

void UPicker::RemovePickable() {
	PickedPickable = nullptr;
}