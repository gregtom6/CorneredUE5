// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_MixingMachine.h"

float UConfig_MixingMachine::GetProcessTime(EAbility ability) const {
	for (int i = 0; i < AbilityProcessTimeEntries.Num(); i++) {
		if (AbilityProcessTimeEntries[i].Key == ability) {
			return AbilityProcessTimeEntries[i].ProcessTime;
		}
	}

	return 0.f;
}