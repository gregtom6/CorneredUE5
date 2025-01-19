// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Progress.h"
#include "System/CorneredGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "System/ProgressionGameState.h"

bool UConfig_Progress::IsAbilityAlreadyUnlocked(EAbility ability, UCorneredGameInstance* gameInstance) {
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

int32 UConfig_Progress::GetSoulBorderCount(UWorld* World) {

    const UWorld* CastedWorld = Cast<UWorld>(World);
    if (!CastedWorld)
    {
        return -1;
    }

    for (int i = 0; i < SoulBorderCountsPerLevel.Num(); i++) {
        
        const UWorld* LevelPtr = SoulBorderCountsPerLevel[i].Level.Get();
        if (LevelPtr && LevelPtr->GetName() == CastedWorld->GetName())
        {
            return SoulBorderCountsPerLevel[i].SoulBorder;
        }
    }

    return -1;
}

int UConfig_Progress::GetMaxUnlockLevel() const {
    return AbilitiesToUnlockPerLevel.Num();
}

bool UConfig_Progress::IsAbilityUnlocked(EAbility Ability, AProgressionGameState* GameState) {
    if (Ability == EAbility::Default) {
        return true;
    }

    if (GameState)
    {
        TArray<EAbility> unlockedAbilities = GetAlreadyUnlockedAbilities(GameState->UnlockLevel);
        return unlockedAbilities.Contains(Ability);
    }

    return false;
}