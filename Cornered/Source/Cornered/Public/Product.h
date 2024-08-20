// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "Product.generated.h"

class UEquipmentVisualizer;
class UInventory;
/**
 *
 */
UCLASS()
class CORNERED_API AProduct : public AIngredient, public IEquippable
{
	GENERATED_BODY()

protected:

		virtual void Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) override;

		virtual IEquippable* GetEquippable() const override;
};
