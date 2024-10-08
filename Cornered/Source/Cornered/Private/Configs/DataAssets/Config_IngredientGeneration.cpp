// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_IngredientGeneration.h"
#include "Items/Ingredient.h"

TSubclassOf<AIngredient> UConfig_IngredientGeneration::GetWeightedRandomItemClass() const {
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