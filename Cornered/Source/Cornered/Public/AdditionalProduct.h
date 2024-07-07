// Fill out your copyright notice in the Description page of Project Settings.

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
