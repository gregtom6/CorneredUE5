// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemType.h"
#include "ItemMaterial.generated.h"

class UMaterialInterface;

USTRUCT(BlueprintType)
struct FItemMaterial {

	GENERATED_BODY()

	FItemMaterial()
		: Key(EItemType::Count) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TObjectPtr<UMaterialInterface> Material;
};