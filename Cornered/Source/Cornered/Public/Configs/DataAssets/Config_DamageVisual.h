// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_DamageVisual.generated.h"

class UMaterialInterface;

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_DamageVisual : public UDataAsset
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	UMaterialInterface* NormalMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* DamagedMaterial;

	UPROPERTY(EditAnywhere)
	TArray<float> DamageStepPercentages;

public:

	TArray<float> GetDamagePercentages();

	int GetCountOfDamagePercentages();

	UMaterialInterface* GetSelectedMaterial(bool isDamaged);
	
};
