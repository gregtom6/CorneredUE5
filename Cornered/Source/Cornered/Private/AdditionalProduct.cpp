// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "AdditionalProduct.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"

void AAdditionalProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory);
}