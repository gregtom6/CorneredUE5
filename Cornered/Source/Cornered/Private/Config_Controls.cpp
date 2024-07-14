// Fill out your copyright notice in the Description page of Project Settings.


#include "Config_Controls.h"

int32 UConfig_Controls::GetControlsPageCount() {
    return ControlsPageDatas.Num();
}

FControlsPageDatas UConfig_Controls::GetControlsPageDatas(int32 index) {
    if (index < ControlsPageDatas.Num())
    {
        return ControlsPageDatas[index];
    }

    return FControlsPageDatas();
}