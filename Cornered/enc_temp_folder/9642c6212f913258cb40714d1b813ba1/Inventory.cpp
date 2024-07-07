// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Product.h"
#include "WeaponProduct.h"
#include "AdditionalProduct.h"
#include "ShieldProduct.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventory::EquipItem(AProduct* Product) {

	if (Product->IsA(AWeaponProduct::StaticClass())) {
		Weapon = Product->GetItemType();
	}
	else if (Product->IsA(AShieldProduct::StaticClass())) {
		Shield = Product->GetItemType();
	}
	else if (Product->IsA(AAdditionalProduct::StaticClass())) {
		Additional = Product->GetItemType();
	}
}

EItemType UInventory::GetWeapon() const {
	return Weapon;
}
