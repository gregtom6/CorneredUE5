// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "MainMenu.h"

AMainMenuHUD::AMainMenuHUD() {
    MainMenuBGMComp = CreateDefaultSubobject<UAudioComponent>(TEXT("MainMenuBGMComp"));
    SFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComp"));
}

void AMainMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (UserWidgetClass)
    {
        UserWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
        if (UserWidgetInstance)
        {
            UserWidgetInstance->AddToViewport();
            UMainMenu* mainMenu = Cast<UMainMenu>(UserWidgetInstance);

            if (mainMenu) {
                mainMenu->UIPressHappened.AddUniqueDynamic(this, &AMainMenuHUD::UIPressHappened);
            }
        }
    }
}

void AMainMenuHUD::UIPressHappened() {
    SFXComp->Play();
}