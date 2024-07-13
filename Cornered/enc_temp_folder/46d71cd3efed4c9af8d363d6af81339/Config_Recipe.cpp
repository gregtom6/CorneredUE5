// Fill out your copyright notice in the Description page of Project Settings.


#include "Config_Recipe.h"
#include "Ingredient.h"

TSubclassOf<AIngredient> UConfig_Recipe::GetResultItem(TArray<EItemType> detectedItems) {
    
    EItemType resultItemType;

    for (int i = 0; i < RecipeEntries.Num(); i++)
    {
        int equalElements = 0;
        
        for (int j = 0; j < RecipeEntries[i].Items.Num(); j++) {

            if (GetOccurrenceNumber(RecipeEntries[i].Items, RecipeEntries[i].Items[j]) == GetOccurrenceNumber(detectedItems, RecipeEntries[i].Items[j])) {
                equalElements += 1;
            }

        }

        if (equalElements == detectedItems.Num()) {
            resultItemType = RecipeEntries[i].Key;
            break;
        }
    }

    for (int i = 0; i < ProductClassEntries.Num(); i++) {
        if (ProductClassEntries[i].Key == resultItemType) {
            return ProductClassEntries[i].IngredientClass;
        }
    }

    return nullptr;
}

int32 UConfig_Recipe::GetOccurrenceNumber(TArray<EItemType> array, EItemType element) {
    int32 count = 0;
    for (int i = 0; i < array.Num(); i++) {
        if (array[i] == element) {
            count += 1;
        }
    }
    return count;
}