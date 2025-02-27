// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/ExternalEquipper.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Characters/ActorComponents/Inventory.h"
#include "Items/Equippable.h"

UExternalEquipper::UExternalEquipper()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UExternalEquipper::Equip(FItemData weapon, FItemData shield, FItemData additional) {
	
	UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();
	UInventory* inventory = GetOwner()->FindComponentByClass<UInventory>();

	inventory->EquipWeapon(weapon);
	inventory->EquipShield(shield);
	inventory->EquipAdditional(additional);

	equipmentVisualizer->VisualizeWeaponDatas(weapon);
}
