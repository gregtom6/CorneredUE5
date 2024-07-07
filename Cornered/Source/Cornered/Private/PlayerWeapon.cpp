// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon.h"
#include "Inventory.h"

EItemType UPlayerWeapon::GetEquippedWeapon() const {
	
	UInventory* inventory = Cast<UInventory>(GetOwner()->GetComponentByClass(UInventory::StaticClass()));
	return inventory->GetWeapon();
}