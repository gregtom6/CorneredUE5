// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Controls.h"

int32 UConfig_Controls::GetControlsPageCount() const {
    return ControlsPageDatas.Num();
}

FControlsPageDatas UConfig_Controls::GetControlsPageDatas(int32 index) const {
    if (index < ControlsPageDatas.Num())
    {
        return ControlsPageDatas[index];
    }

    return FControlsPageDatas();
}