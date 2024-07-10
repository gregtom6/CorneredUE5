// Fill out your copyright notice in the Description page of Project Settings.


#include "Config_IngredientGeneration.h"
#include "Ingredient.h"

TSubclassOf<AIngredient> UConfig_IngredientGeneration::GetWeightedRandomItemClass() {
    int SumOfWeights = 0;

    for(int i=0;i< IngredientGenerationEntries.Num();i++)
    {
        SumOfWeights += IngredientGenerationEntries[i].WeightForAppear;
    }

    int random = FMath::RandRange(0, SumOfWeights);

    SumOfWeights = 0;

    for (int i = 0; i < IngredientGenerationEntries.Num(); i++)
    {
        SumOfWeights += IngredientGenerationEntries[i].WeightForAppear;
        if (SumOfWeights >= random)
        {
            return IngredientGenerationEntries[i].IngredientClass;
        }
    }

    return nullptr;
}