// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProduct.h"
#include "EquipmentVisualizer.h"
#include "Inventory.h"

void AWeaponProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) {

	inventory->EquipItem(this);

	equipmentVisualizer->VisualizeEquipment(this);

	AProduct::Equip(equipmentVisualizer, inventory);
}