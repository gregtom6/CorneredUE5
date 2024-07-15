// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Product.h"
#include "AdditionalProduct.generated.h"

class UEquipmentVisualizer;
class UInventory;
/**
 * 
 */
UCLASS()
class CORNERED_API AAdditionalProduct : public AProduct
{
	GENERATED_BODY()
	
protected:

	virtual void Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) override;
};
