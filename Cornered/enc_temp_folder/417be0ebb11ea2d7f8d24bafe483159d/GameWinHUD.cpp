// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "GameWinHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "GameWinMenu.h"

AGameWinHUD::AGameWinHUD() {
    GameWinBGMComp = CreateDefaultSubobject<UAudioComponent>(TEXT("GameWinBGMComp"));
    SFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComp"));
}

void AGameWinHUD::BeginPlay()
{
    Super::BeginPlay();

    if (UserWidgetClass)
    {
        UserWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
        if (UserWidgetInstance)
        {
            UserWidgetInstance->AddToViewport();
            UGameWinMenu* mainMenu = Cast<UGameWinMenu>(UserWidgetInstance);

            if (mainMenu) {
                mainMenu->UIPressHappened.AddUniqueDynamic(this, &AGameWinHUD::UIPressHappened);
            }
        }
    }
}

void AGameWinHUD::UIPressHappened() {
    SFXComp->Play();
}