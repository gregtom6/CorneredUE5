// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Items/Equippable.h"
#include "Pickable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickable : public UInterface
{
	GENERATED_BODY()
};

class CORNERED_API IPickable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Pickup(AActor* Actor) = 0;

	virtual void Drop() = 0;

	virtual bool IsPicked() const = 0;

	virtual bool WasPickedAnytime() const = 0;

	virtual IEquippable* GetEquippable() const = 0;
};
