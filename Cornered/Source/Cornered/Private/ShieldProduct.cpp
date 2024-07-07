// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldProduct.h"
#include "EquipmentVisualizer.h"

void AShieldProduct::Equip(UEquipmentVisualizer* equipmentVisualizer) {

	equipmentVisualizer->VisualizeEquipment(ItemType);

	AProduct::Equip(equipmentVisualizer);
}