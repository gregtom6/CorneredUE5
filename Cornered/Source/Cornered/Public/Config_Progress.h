// Fill out your copyright notice in the Description page of Project Settings.

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

private:

    UFUNCTION()
        TArray<EAbility> GetAlreadyUnlockedAbilities(int currentUnlockLevel) const;

    UPROPERTY(EditAnywhere)
        TArray<FUnlockableAbilities> AbilitiesToUnlockPerLevel;
	
};
