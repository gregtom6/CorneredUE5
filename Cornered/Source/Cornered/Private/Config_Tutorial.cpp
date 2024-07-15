// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Config_Tutorial.h"

int32 UConfig_Tutorial::GetTutorialPageCount() {
	return TutorialPageDatas.Num();
}

FTutorialPageDatas UConfig_Tutorial::GetTutorialPageDatas(int32 index) {
    if (index < TutorialPageDatas.Num())
    {
        return TutorialPageDatas[index];
    }

    return FTutorialPageDatas();
}