// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Tutorial.h"

int32 UConfig_Tutorial::GetTutorialPageCount() const {
	return TutorialPageDatas.Num();
}

FTutorialPageDatas UConfig_Tutorial::GetTutorialPageDatas(int32 index) const {
    if (index < TutorialPageDatas.Num())
    {
        return TutorialPageDatas[index];
    }

    return FTutorialPageDatas();
}