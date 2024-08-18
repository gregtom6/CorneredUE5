// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ExternalEquipper.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"
#include "Equippable.h"

// Sets default values for this component's properties
UExternalEquipper::UExternalEquipper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UExternalEquipper::Equip(FItemDatas weapon, FItemDatas shield, FItemDatas additional) {
	
	UEquipmentVisualizer* equipmentVisualizer = Cast<UEquipmentVisualizer>(GetOwner()->GetComponentByClass(UEquipmentVisualizer::StaticClass()));
	UInventory* inventory = Cast<UInventory>(GetOwner()->GetComponentByClass(UInventory::StaticClass()));

	inventory->EquipWeapon(weapon);
	inventory->EquipShield(shield);
	inventory->EquipAdditional(additional);

	equipmentVisualizer->VisualizeWeaponDatas(weapon);
}
