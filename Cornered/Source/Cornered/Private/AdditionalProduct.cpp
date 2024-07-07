// Fill out your copyright notice in the Description page of Project Settings.


#include "AdditionalProduct.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"

void AAdditionalProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory);
}