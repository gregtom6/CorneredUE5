// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Product.h"
#include "ShieldProduct.generated.h"

class UEquipmentVisualizer;
class UInventory;
class UCameraComponent;
class UConfig_Equipment;
/**
 *
 */
UCLASS()
class CORNERED_API AShieldProduct : public AProduct
{
	GENERATED_BODY()

protected:

	virtual void Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory, UCameraComponent* camera, UConfig_Equipment* config) override;
};
