// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MovableCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8 {
	Standing,
	Walking,
	Strafing,

	Count,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMovableCharacter : public UInterface
{
	GENERATED_BODY()
};

class CORNERED_API IMovableCharacter
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual EMovementState GetMovementState() const = 0;
};
