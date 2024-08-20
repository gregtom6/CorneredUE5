// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterWeapon.h"
#include "Config_Hint.generated.h"

class UMaterialInterface;

USTRUCT(BlueprintType)
struct FItemHintMaterialEntry
{
	GENERATED_BODY()

		FItemHintMaterialEntry()
		: Key(EItemType::Count) { }

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		TObjectPtr<UMaterialInterface> Material;

};


/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Hint : public UDataAsset
{
	GENERATED_BODY()
	
private:
		UPROPERTY(EditAnywhere, Category = "Dictionary")
		TArray<FItemHintMaterialEntry> ItemHintMaterialDict;

public:

	UFUNCTION()
		UMaterialInterface* GetMaterialBasedOnItemType(EItemType itemType);
};
