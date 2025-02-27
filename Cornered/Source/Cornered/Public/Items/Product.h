// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Ingredient.h"
#include "Product.generated.h"

class UEquipmentVisualizer;
class UInventory;
class UCameraComponent;
class UConfig_Equipment;
/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProductEquipEnded);

UCLASS()
class CORNERED_API AProduct : public AIngredient, public IEquippable
{
	GENERATED_BODY()

public:

	FProductEquipEnded ProductEquipEnded;

private:

	float StartTime;

	bool bCanFlyIntoEquipper;

	FVector StartPosition;
	FVector TargetPosition;

	UPROPERTY()
	TObjectPtr<UConfig_Equipment> Config;

	UPROPERTY()
	TObjectPtr<UCameraComponent> EquipperCamera;

public:

	AProduct();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory, UCameraComponent* camera, UConfig_Equipment* EquipmentConfig) override;

	virtual IEquippable* GetEquippable() const override;

	void ArrivedIntoEquipper();

};
