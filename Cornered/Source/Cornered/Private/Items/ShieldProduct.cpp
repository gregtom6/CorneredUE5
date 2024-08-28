// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Items/ShieldProduct.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Characters/ActorComponents/Inventory.h"

void AShieldProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory);
}