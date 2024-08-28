// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Materials/MaterialInterface.h"
#include "Config_Belt.generated.h"

UENUM()
enum class EBeltSpeed : uint8 {
	Normal,
	Fastened,

	Count,
};


USTRUCT(BlueprintType)
struct FBeltSpeedMaterialEntry
{
	GENERATED_BODY()

		FBeltSpeedMaterialEntry()
		: Key(EBeltSpeed::Count) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		EBeltSpeed Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		TObjectPtr<UMaterialInterface> Material;

};


class ABeltElement;
/**
 *
 */
UCLASS()
class CORNERED_API UConfig_Belt : public UDataAsset
{
	GENERATED_BODY()


private:

	UPROPERTY(EditAnywhere)
		float NormalMultiplier;
	UPROPERTY(EditAnywhere)
		float SpeedMultiplier;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABeltElement> BeltElementClass;

	UPROPERTY(EditAnywhere, Category = "Dictionary")
		TArray<FBeltSpeedMaterialEntry> BeltSpeedMaterialEntries;

public:

	UFUNCTION()
		float GetCurrentMultiplier(EBeltSpeed beltSpeed) const;

	UFUNCTION()
		TSubclassOf<ABeltElement> GetBeltElementClass() const;

	UFUNCTION()
		UMaterialInterface* GetMaterialBasedOnSpeed(EBeltSpeed speed) const;
};
