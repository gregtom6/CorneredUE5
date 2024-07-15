// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ShieldProduct.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"

void AShieldProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory);
}