// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Characters/ActorComponents/CharacterWeapon.h"
#include "Config_IngredientGeneration.generated.h"

class AIngredient;

USTRUCT(BlueprintType)
struct FIngredientEntry
{
	GENERATED_BODY()

		FIngredientEntry()
		: Key(EItemType::Count), WeightForAppear(0) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		int WeightForAppear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		TSubclassOf<AIngredient> IngredientClass;

};

UCLASS()
class CORNERED_API UConfig_IngredientGeneration : public UDataAsset
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Dictionary")
		TArray<FIngredientEntry> IngredientGenerationEntries;

public:

	UFUNCTION()
		TSubclassOf<AIngredient> GetWeightedRandomItemClass() const;

};
