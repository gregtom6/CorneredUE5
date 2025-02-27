// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Characters/ActorComponents/CharacterWeapon.h"
#include "Items/ItemMaterial.h"
#include "Config_Hint.generated.h"

class UMaterialInterface;

UCLASS()
class CORNERED_API UConfig_Hint : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Dictionary")
	TArray<FItemMaterial> ItemHintMaterialDict;

public:

	UMaterialInterface* GetMaterialBasedOnItemType(EItemType itemType) const;
};
