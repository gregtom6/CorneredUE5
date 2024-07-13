// Fill out your copyright notice in the Description page of Project Settings.


#include "Config_Recipe.h"
#include "Ingredient.h"
#include "MixingItemDetector.h"

TSubclassOf<AIngredient> UConfig_Recipe::GetResultItem(TArray<FItemData> detectedItems) {
    
    EItemType resultItemType;

    for (int i = 0; i < RecipeEntries.Num(); i++)
    {
        int equalElements = 0;
        
        for (int j = 0; j < RecipeEntries[i].Items.Num(); j++) {

            if (GetOccurrenceNumber(RecipeEntries[i].Items, RecipeEntries[i].Items[j].ItemType, RecipeEntries[i].Items[j].ItemState) == GetOccurrenceNumber(detectedItems, RecipeEntries[i].Items[j].ItemType, RecipeEntries[i].Items[j].ItemState)) {
                equalElements += 1;
            }

        }

        if (equalElements == RecipeEntries[i].Items.Num()) {
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

int32 UConfig_Recipe::GetOccurrenceNumber(TArray<FItemData> array, EItemType element, EItemState itemState) {
    int32 count = 0;
    for (int i = 0; i < array.Num(); i++) {
        if (array[i].ItemType == element && array[i].ItemState==itemState) {
            count += 1;
        }
    }
    return count;
}