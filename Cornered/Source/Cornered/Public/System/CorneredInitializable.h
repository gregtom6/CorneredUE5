// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CorneredInitializable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCorneredInitializable : public UInterface
{
	GENERATED_BODY()
};

class CORNERED_API ICorneredInitializable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void InitializeHappened() = 0;
};
