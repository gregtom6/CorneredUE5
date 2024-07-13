// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterWeapon.h"
#include "Config_Recipe.generated.h"

class AIngredient;

USTRUCT(BlueprintType)
struct FRecipeEntry
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

public:

	TSubclassOf<AIngredient> GetResultItem(EItemType itemType);
};
