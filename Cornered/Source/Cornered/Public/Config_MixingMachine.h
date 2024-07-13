// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_MixingMachine.generated.h"

UENUM(BlueprintType)
enum class EAbility : uint8
{
    Default,
    Burn,
    Freeze,

    Count,
};

USTRUCT(BlueprintType)
struct FAbilityProcessTimeEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EAbility Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        float ProcessTime;

};

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_MixingMachine : public UDataAsset
{
	GENERATED_BODY()

private:

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FAbilityProcessTimeEntry> AbilityProcessTimeEntries;

public:

    UFUNCTION()
        float GetProcessTime(EAbility ability);
	
};
