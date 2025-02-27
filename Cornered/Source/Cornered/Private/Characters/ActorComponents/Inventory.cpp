// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/Inventory.h"
#include "Items/Product.h"
#include "Items/WeaponProduct.h"
#include "Items/AdditionalProduct.h"
#include "Items/ShieldProduct.h"
#include "Configs/DataAssets/Config_Equipment.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	Weapon = EItemType::Count;
	Shield = EItemType::Count;
	Additional = EItemType::Count;
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

void UInventory::EquipWeapon(FItemData itemDatas) {
	Weapon = itemDatas.ItemType;
}

void UInventory::EquipShield(FItemData itemDatas) {
	Shield = itemDatas.ItemType;
}

void UInventory::EquipAdditional(FItemData itemDatas) {
	Additional = itemDatas.ItemType;
}

EItemType UInventory::GetWeapon() const {
	return Weapon;
}
