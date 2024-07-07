// Fill out your copyright notice in the Description page of Project Settings.


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