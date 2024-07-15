// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Equippable.generated.h"

class UEquipmentVisualizer;
class UInventory;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquippable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CORNERED_API IEquippable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory) = 0;
};
