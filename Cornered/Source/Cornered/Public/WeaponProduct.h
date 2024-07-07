// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Product.h"
#include "WeaponProduct.generated.h"

class UEquipmentVisualizer;

/**
 * 
 */
UCLASS()
class CORNERED_API AWeaponProduct : public AProduct
{
	GENERATED_BODY()
	
protected:

	virtual void Equip(UEquipmentVisualizer* equipmentVisualizer) override;
};
