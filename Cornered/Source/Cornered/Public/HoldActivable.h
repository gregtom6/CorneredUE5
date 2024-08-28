// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoldActivable.generated.h"

UCLASS(Abstract)
class CORNERED_API AHoldActivable : public AActor
{
	GENERATED_BODY()

public:

	virtual void HoldProcessStarted() PURE_VIRTUAL(AHoldActivable::HoldProcessStarted, );

	virtual void HoldProcessEnded() PURE_VIRTUAL(AHoldActivable::HoldProcessEnded, );
};
