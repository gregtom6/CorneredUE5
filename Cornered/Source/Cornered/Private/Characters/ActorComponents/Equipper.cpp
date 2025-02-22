// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/Equipper.h"
#include "Characters/ActorComponents/Picker.h"
#include <Kismet/GameplayStatics.h>
#include "Items/Equippable.h"
#include "System/CorneredPlayerController.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Characters/ActorComponents/Inventory.h"
#include "Components/AudioComponent.h"
#include "Camera/CameraComponent.h"
#include "Items/Product.h"
#include "Configs/DataAssets/Config_Equipment.h"

void UEquipper::BeginPlay()
{
	Super::BeginPlay();

	PickerComp = GetOwner()->FindComponentByClass<UPicker>();

	State = EPickedFlyState::NotFlying;

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
	if (PickerComp && PickerComp->GetPickedPickable() && State == EPickedFlyState::NotFlying) {
		IEquippable* equippable = PickerComp->GetPickedPickable()->GetEquippable();
		if (equippable) {

			UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();
			UCameraComponent* camera = GetOwner()->FindComponentByClass<UCameraComponent>();
			UInventory* inventory = GetOwner()->FindComponentByClass<UInventory>();

			UAudioComponent* equipAudio = GetOwner()->FindComponentByClass<UAudioComponent>();
			equipAudio->Play();

			PickerComp->RemovePickable();
			equippable->Equip(equipmentVisualizer, inventory, camera, EquipmentConfig);

			State = EPickedFlyState::Flying;

			if (AProduct* ActorInstance = Cast<AProduct>(equippable)) {

				ActorInstance->ProductEquipEnded.AddUniqueDynamic(this, &UEquipper::ActualEquip);
			}
			else {
				ActualEquip();
			}
		}
	}
}

void UEquipper::ActualEquip() {

	State = EPickedFlyState::NotFlying;
}