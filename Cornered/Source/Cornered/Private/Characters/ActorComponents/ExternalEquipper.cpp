// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/ExternalEquipper.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Characters/ActorComponents/Inventory.h"
#include "Items/Equippable.h"

// Sets default values for this component's properties
UExternalEquipper::UExternalEquipper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UExternalEquipper::Equip(FItemDatas weapon, FItemDatas shield, FItemDatas additional) {
	
	UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();
	UInventory* inventory = GetOwner()->FindComponentByClass<UInventory>();

	inventory->EquipWeapon(weapon);
	inventory->EquipShield(shield);
	inventory->EquipAdditional(additional);

	equipmentVisualizer->VisualizeWeaponDatas(weapon);
}
