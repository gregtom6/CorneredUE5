// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/Equipper.h"
#include "Characters/ActorComponents/Picker.h"
#include <Kismet/GameplayStatics.h>
#include "Items/Equippable.h"
#include "System/CorneredPlayerController.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Characters/ActorComponents/Inventory.h"
#include "Components/AudioComponent.h"

UEquipper::UEquipper()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipper::BeginPlay()
{
	Super::BeginPlay();

	PickerComp = GetOwner()->FindComponentByClass<UPicker>();

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

			UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();
			UAudioComponent* equipAudio = GetOwner()->FindComponentByClass<UAudioComponent>();

			UInventory* inventory = GetOwner()->FindComponentByClass<UInventory>();

			PickerComp->RemovePickable();
			equippable->Equip(equipmentVisualizer, inventory);

			equipAudio->Play();
		}
	}
}