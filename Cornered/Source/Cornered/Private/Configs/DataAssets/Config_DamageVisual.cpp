// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_DamageVisual.h"
#include "Materials/MaterialInterface.h"

TArray<float> UConfig_DamageVisual::GetDamagePercentages() {
	return DamageStepPercentages;
}

int UConfig_DamageVisual::GetCountOfDamagePercentages() {
	return DamageStepPercentages.Num();
}

UMaterialInterface* UConfig_DamageVisual::GetSelectedMaterial(bool isDamaged) {
	if (isDamaged) {
		return DamagedMaterial;
	}

	return NormalMaterial;
}