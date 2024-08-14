#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    EmptyItem,
    Tube,
    Marbles,
    Board,
    Coffee,
    Boots,
    Petrol,
    Pistol,
    Shotgun,
    FastBoots,
    FlamingShotgun,
    Freezer,
    DefenderPhysical,
    DefenderPhysicalExtra,
    DefenderHeat,
    DefenderCold,
    Rope,

    Count,
};