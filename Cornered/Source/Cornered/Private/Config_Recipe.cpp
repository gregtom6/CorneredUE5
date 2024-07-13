// Fill out your copyright notice in the Description page of Project Settings.


#include "Config_Recipe.h"
#include "Ingredient.h"

TSubclassOf<AIngredient> UConfig_Recipe::GetResultItem(EItemType itemType) {
    for (int i = 0; i < RecipeEntries.Num(); i++)
    {
        if (RecipeEntries[i].Key == itemType) {
            return RecipeEntries[i].IngredientClass;
        }
    }

    return nullptr;
}