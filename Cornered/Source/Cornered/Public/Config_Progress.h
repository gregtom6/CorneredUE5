// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_MixingMachine.h"
#include "Config_Progress.generated.h"

USTRUCT(BlueprintType)
struct FUnlockableAbilities
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TArray<EAbility> Abilities;
};

class UCorneredGameInstance;
class AProgressionGameState;

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Progress : public UDataAsset
{
	GENERATED_BODY()

public:

    UFUNCTION()
    bool IsAbilityAlreadyUnlocked(EAbility ability, UCorneredGameInstance* gameInstance) const;

    UFUNCTION()
        int GetMaxUnlockLevel();

    UFUNCTION()
        bool IsAbilityUnlocked(EAbility Ability, AProgressionGameState* GameState);

private:

    UFUNCTION()
        TArray<EAbility> GetAlreadyUnlockedAbilities(int currentUnlockLevel) const;

    UPROPERTY(EditAnywhere)
        TArray<FUnlockableAbilities> AbilitiesToUnlockPerLevel;
	
};
