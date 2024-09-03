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

void UInventory::EquipWeapon(FItemDatas itemDatas) {
	Weapon = itemDatas.Key;
}

void UInventory::EquipShield(FItemDatas itemDatas) {
	Shield = itemDatas.Key;
}

void UInventory::EquipAdditional(FItemDatas itemDatas) {
	Additional = itemDatas.Key;
}

EItemType UInventory::GetWeapon() const {
	return Weapon;
}
