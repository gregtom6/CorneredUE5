// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Equipper.h"
#include "Picker.h"
#include <Kismet/GameplayStatics.h>
#include "Equippable.h"
#include <CorneredPlayerController.h>
#include "EquipmentVisualizer.h"
#include "Inventory.h"
#include "Components/AudioComponent.h"

UEquipper::UEquipper()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipper::BeginPlay()
{
	Super::BeginPlay();

	PickerComp = Cast<UPicker>(GetOwner()->GetComponentByClass(UPicker::StaticClass()));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ACorneredPlayerController* CustomPlayerController = Cast<ACorneredPlayerController>(PlayerController);
		if (CustomPlayerController)
		{
			CustomPlayerController->EquipHappenedInstance.AddUniqueDynamic(this, &UEquipper::EquipHappened);
		}
	}
	
}

void UEquipper::EquipHappened() {
	if (PickerComp && PickerComp->GetPickedPickable()) {
		IEquippable* equippable = PickerComp->GetPickedPickable()->GetEquippable();
		if (equippable) {

			UEquipmentVisualizer* equipmentVisualizer = Cast<UEquipmentVisualizer>(GetOwner()->GetComponentByClass(UEquipmentVisualizer::StaticClass()));
			UAudioComponent* equipAudio = Cast<UAudioComponent>(GetOwner()->GetComponentByClass(UAudioComponent::StaticClass()));

			UInventory* inventory = Cast<UInventory>(GetOwner()->GetComponentByClass(UInventory::StaticClass()));

			PickerComp->RemovePickable();
			equippable->Equip(equipmentVisualizer, inventory);

			equipAudio->Play();
		}
	}
}