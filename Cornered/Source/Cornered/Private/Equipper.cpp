// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipper.h"
#include "Picker.h"
#include <Kismet/GameplayStatics.h>
#include "Equippable.h"
#include <CorneredPlayerController.h>
#include "EquipmentVisualizer.h"
#include "Inventory.h"
#include "Components/AudioComponent.h"


// Sets default values for this component's properties
UEquipper::UEquipper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
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


// Called every frame
void UEquipper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

