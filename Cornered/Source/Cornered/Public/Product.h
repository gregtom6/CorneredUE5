// Fill out your copyright notice in the Description page of Project Settings.

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

		UFUNCTION()
		// Inherited via IEquippable
		virtual void Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) override;

		virtual IEquippable* GetEquippable() const override;
};
