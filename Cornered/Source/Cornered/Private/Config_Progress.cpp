// Fill out your copyright notice in the Description page of Project Settings.


#include "Config_Progress.h"
#include "CorneredGameInstance.h"
#include <Kismet/GameplayStatics.h>

bool UConfig_Progress::IsAbilityAlreadyUnlocked(EAbility ability, UCorneredGameInstance* gameInstance) const {
    if (ability == EAbility::Default)
    {
        return true;
    }

    int32 currentUnlockLevel = gameInstance->GetCurrentUnlockLevel();

    TArray<EAbility> unlockedAbilities = GetAlreadyUnlockedAbilities(currentUnlockLevel);

    return unlockedAbilities.Contains(ability);
}

TArray<EAbility> UConfig_Progress::GetAlreadyUnlockedAbilities(int32 currentUnlockLevel) const {
    TArray<EAbility> abilities;

    currentUnlockLevel = FMath::Min(AbilitiesToUnlockPerLevel.Num() - 1, currentUnlockLevel);

    for (int i = currentUnlockLevel; i >= 0; i--)
    {
        abilities.Append(AbilitiesToUnlockPerLevel[i].Abilities);
    }

    return abilities;
}