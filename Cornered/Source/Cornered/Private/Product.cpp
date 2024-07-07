// Fill out your copyright notice in the Description page of Project Settings.


#include "Product.h"
#include "EquipmentVisualizer.h"

void AProduct::Equip(UEquipmentVisualizer* equipmentVisualizer)
{
	Destroy();
}

IEquippable* AProduct::GetEquippable() const {
	return const_cast<IEquippable*>(static_cast<const IEquippable*>(this));
}