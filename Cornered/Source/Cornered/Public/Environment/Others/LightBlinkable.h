// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LightBlinkable.generated.h"

class ULightComponent;
class UMaterialInstanceDynamic;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULightBlinkable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CORNERED_API ILightBlinkable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual TArray<ULightComponent*> GetLightComponents() = 0;
	virtual TArray<UMaterialInstanceDynamic*> GetLightMaterials() = 0;
};
