// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterWeapon.h"
#include "Config_MixingMachine.h"
#include "Config_Recipe.generated.h"

class AIngredient;
class UMaterialInterface;
class UConfig_Progress;
class UCorneredGameInstance;

USTRUCT(BlueprintType)
struct FRecipeEntry
{
    GENERATED_BODY()

        FRecipeEntry()
        : Key(EItemType::Count), NecessaryAbilityToUSe(EAbility::Count){ }

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

        FProductClassEntry()
        : Key(EItemType::Count) { }

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TSubclassOf<AIngredient> IngredientClass;

};

USTRUCT(BlueprintType)
struct FIngredientRadiatingMaterialEntry {

    GENERATED_BODY()

        FIngredientRadiatingMaterialEntry()
        : Key(EItemType::Count) { }

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TObjectPtr<UMaterialInterface> Material;
};

USTRUCT(BlueprintType)
struct FEffectRadiatingMaterialEntry {

    GENERATED_BODY()

        FEffectRadiatingMaterialEntry()
        : Key(EItemState::Count) { }

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemState Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TObjectPtr<UMaterialInterface> Material;
};

USTRUCT(BlueprintType)
struct FMaterialArray
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<TObjectPtr<UMaterialInterface>> Materials;
};

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Recipe : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere)
        TObjectPtr<UMaterialInterface> RecipeShowPlusMaterial;

    UPROPERTY(EditAnywhere)
        TObjectPtr<UMaterialInterface> RecipeShowEqualMaterial;

    UPROPERTY(EditAnywhere)
        TSubclassOf<AActor> RecipeShowElementClass;

    UPROPERTY(EditAnywhere)
        TSubclassOf<AActor> RecipeShowOperatorClass;

private:

    UPROPERTY(EditAnywhere)
        UConfig_Progress* ProgressConfig;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FRecipeEntry> RecipeEntries;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FProductClassEntry> ProductClassEntries;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray< FIngredientRadiatingMaterialEntry> IngredientRadiatingMaterialEntries;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray< FEffectRadiatingMaterialEntry> EffectRadiatingMaterialEntries;

public:

	TSubclassOf<AIngredient> GetResultItem(TArray<FItemData> detectedItems) const;

    UFUNCTION()
        TArray<FMaterialArray> GetRadiatingMaterialsOfAllRecipes(TArray<FMaterialArray>& EffectMaterials, UCorneredGameInstance* GameInstance) const;

private:

    UFUNCTION()
        int32 GetOccurrenceNumber(TArray<FItemData> array, EItemType element, EItemState itemState) const;

    UFUNCTION()
        UMaterialInterface* GetRadiatingMaterial(EItemType itemType) const;

    UFUNCTION()
        UMaterialInterface* GetRadiatingEffectMaterial(EItemState itemState) const;

};
