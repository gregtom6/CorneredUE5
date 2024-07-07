// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldProduct.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"

void AShieldProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory);
}