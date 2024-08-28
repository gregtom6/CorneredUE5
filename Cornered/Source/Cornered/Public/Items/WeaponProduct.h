// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Product.h"
#include "WeaponProduct.generated.h"

class UEquipmentVisualizer;
class UInventory;
/**
 *
 */
UCLASS()
class CORNERED_API AWeaponProduct : public AProduct
{
	GENERATED_BODY()

protected:

	virtual void Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) override;
};
