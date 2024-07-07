// Fill out your copyright notice in the Description page of Project Settings.


#include "AdditionalProduct.h"
#include "EquipmentVisualizer.h"

void AAdditionalProduct::Equip(UEquipmentVisualizer* equipmentVisualizer) {

	equipmentVisualizer->VisualizeEquipment(ItemType);

	AProduct::Equip(equipmentVisualizer);
}