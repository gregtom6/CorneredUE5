// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProduct.h"
#include "EquipmentVisualizer.h"

void AWeaponProduct::Equip(UEquipmentVisualizer* equipmentVisualizer) {

	equipmentVisualizer->VisualizeEquipment(ItemType);

	AProduct::Equip(equipmentVisualizer);
}