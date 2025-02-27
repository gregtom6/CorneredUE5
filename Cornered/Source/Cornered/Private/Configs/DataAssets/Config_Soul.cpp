// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Soul.h"
#include "Curves/CurveFloat.h"

float UConfig_Soul::GetIntensityMultiplier(float Time) {
	return LampBlinkingCurve->GetFloatValue(Time);
}