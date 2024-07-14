// Fill out your copyright notice in the Description page of Project Settings.


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