// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Recipe.h"
#include "Items/Ingredient.h"
#include "Environment/MixingMachine/MixingItemDetector.h"
#include "Materials/MaterialInterface.h"
#include "Configs/DataAssets/Config_Progress.h"
#include "System/CorneredGameInstance.h"

TSubclassOf<AIngredient> UConfig_Recipe::GetResultItem(TArray<FItemData> detectedItems) const {

	EItemType resultItemType;

	for (int i = 0; i < RecipeEntries.Num(); i++)
	{
		int equalElements = 0;

		for (int j = 0; j < RecipeEntries[i].Items.Num(); j++) {

			if (GetOccurrenceNumber(RecipeEntries[i].Items, RecipeEntries[i].Items[j].ItemType, RecipeEntries[i].Items[j].ItemState) == GetOccurrenceNumber(detectedItems, RecipeEntries[i].Items[j].ItemType, RecipeEntries[i].Items[j].ItemState)) {
				equalElements += 1;
			}
		}

		if (equalElements == RecipeEntries[i].Items.Num() && equalElements == detectedItems.Num()) {
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

int32 UConfig_Recipe::GetOccurrenceNumber(TArray<FItemData> array, EItemType element, EItemState itemState) const {
	int32 count = 0;
	for (int i = 0; i < array.Num(); i++) {
		if (array[i].ItemType == element && array[i].ItemState == itemState) {
			count += 1;
		}
	}
	return count;
}

TArray<FMaterialArray> UConfig_Recipe::GetRadiatingMaterialsOfAllRecipes(TArray<FMaterialArray>& EffectMaterials, UCorneredGameInstance* GameInstance) const {
	TArray<FMaterialArray> Materials;
	TArray<FMaterialArray> ItemStateMaterials;

	int32 i = 0;

	for (int j = 0; j < RecipeEntries.Num(); j++) {

		FRecipeEntry recipeEntry = RecipeEntries[j];

		if (!ProgressConfig->IsAbilityAlreadyUnlocked(recipeEntry.NecessaryAbilityToUSe, GameInstance)) {
			continue;
		}

		FMaterialArray materialArray;

		Materials.Add(materialArray);
		ItemStateMaterials.Add(materialArray);

		for (int32 k = 0; k < recipeEntry.Items.Num(); k++) {

			UMaterialInterface* mat = GetRadiatingMaterial(recipeEntry.Items[k].ItemType);
			Materials[i].Materials.Add(mat);
			UMaterialInterface* stateMat = GetRadiatingEffectMaterial(recipeEntry.Items[k].ItemState);
			ItemStateMaterials[i].Materials.Add(stateMat);
		}

		UMaterialInterface* endMat = GetRadiatingMaterial(recipeEntry.Key);
		Materials[i].Materials.Add(endMat);
		UMaterialInterface* stateEndMat = GetRadiatingEffectMaterial(EItemState::Normal);
		ItemStateMaterials[i].Materials.Add(stateEndMat);

		i++;
	}

	EffectMaterials = ItemStateMaterials;

	return Materials;
}

UMaterialInterface* UConfig_Recipe::GetRadiatingMaterial(EItemType itemType) const {
	for (int i = 0; i < IngredientRadiatingMaterialEntries.Num(); i++) {
		if (IngredientRadiatingMaterialEntries[i].Key == itemType) {
			return IngredientRadiatingMaterialEntries[i].Material;
		}
	}

	return nullptr;
}

UMaterialInterface* UConfig_Recipe::GetRadiatingEffectMaterial(EItemState itemState) const {
	for (int i = 0; i < EffectRadiatingMaterialEntries.Num(); i++) {
		if (EffectRadiatingMaterialEntries[i].Key == itemState) {
			return EffectRadiatingMaterialEntries[i].Material;
		}
	}

	return nullptr;
}