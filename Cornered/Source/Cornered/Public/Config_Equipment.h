// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterWeapon.h"
#include "Config_Equipment.generated.h"

class AProduct;

USTRUCT(BlueprintType)
struct FEquippedProductEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TSubclassOf<AActor> Value;
};

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Equipment : public UDataAsset
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary")
        TArray<FEquippedProductEntry> EquippedProductEntries;

    UFUNCTION()
        TSubclassOf<AActor> GetEquippedProduct(EItemType itemType) const;
};
