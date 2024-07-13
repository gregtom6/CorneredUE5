// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterWeapon.h"
#include "Config_MixingMachine.h"
#include "Config_Recipe.generated.h"

class AIngredient;


USTRUCT(BlueprintType)
struct FRecipeEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EAbility NecessaryAbilityToUSe;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TArray<FItemData> Items;

};

USTRUCT(BlueprintType)
struct FProductClassEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TSubclassOf<AIngredient> IngredientClass;

};

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Recipe : public UDataAsset
{
	GENERATED_BODY()
	
private:

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FRecipeEntry> RecipeEntries;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FProductClassEntry> ProductClassEntries;

    UFUNCTION()
        int32 GetOccurrenceNumber(TArray<FItemData> array, EItemType element, EItemState itemState);

public:

	TSubclassOf<AIngredient> GetResultItem(TArray<FItemData> detectedItems);
};
