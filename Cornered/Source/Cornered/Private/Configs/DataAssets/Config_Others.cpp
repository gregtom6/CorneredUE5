// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Others.h"
#include "Materials/MaterialInterface.h"


UMaterialInterface* UConfig_Others::GetMaterialBasedOnState(ETimerButtonState state) const {
	for (int i = 0; i < TimerButtonStateMaterialEntries.Num(); i++) {
		if (TimerButtonStateMaterialEntries[i].Key == state) {
			return TimerButtonStateMaterialEntries[i].Material;
		}
	}

	return nullptr;
}