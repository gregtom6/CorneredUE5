// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Hint.h"

UMaterialInterface* UConfig_Hint::GetMaterialBasedOnItemType(EItemType itemType) const {
	for (int i = 0; i < ItemHintMaterialDict.Num();i++) {
		if (ItemHintMaterialDict[i].Key == itemType) {
			return ItemHintMaterialDict[i].Material;
		}
	}

	return nullptr;
}