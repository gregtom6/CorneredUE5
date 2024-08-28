// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Config_Belt.h"

float UConfig_Belt::GetCurrentMultiplier(EBeltSpeed beltSpeed) const {
	return beltSpeed == EBeltSpeed::Normal ? NormalMultiplier : SpeedMultiplier;
}

TSubclassOf<ABeltElement> UConfig_Belt::GetBeltElementClass() const {
	return BeltElementClass;
}

UMaterialInterface* UConfig_Belt::GetMaterialBasedOnSpeed(EBeltSpeed speed) const {
	for (int i = 0; i < BeltSpeedMaterialEntries.Num(); i++) {
		if (BeltSpeedMaterialEntries[i].Key == speed) {
			return BeltSpeedMaterialEntries[i].Material;
		}
	}

	return nullptr;
}