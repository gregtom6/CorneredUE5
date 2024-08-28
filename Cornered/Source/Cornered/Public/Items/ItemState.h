#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ItemState.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
	Normal,
	Freezed,
	Burned,

	Count,
};