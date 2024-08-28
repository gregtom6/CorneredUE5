// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Product.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"

void AProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory)
{
	Destroy();
}

IEquippable* AProduct::GetEquippable() const {
	return const_cast<IEquippable*>(static_cast<const IEquippable*>(this));
}