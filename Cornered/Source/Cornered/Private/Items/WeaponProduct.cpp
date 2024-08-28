// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "WeaponProduct.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"

void AWeaponProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory);
}