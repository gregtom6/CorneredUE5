// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMainMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (UserWidgetClass)
    {
        UserWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
        if (UserWidgetInstance)
        {
            UserWidgetInstance->AddToViewport();
        }
    }
}