// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "GameOverHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "GameOverMenu.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

AGameOverHUD::AGameOverHUD() {
    GameOverBGMComp = CreateDefaultSubobject<UAudioComponent>(TEXT("GameOverBGMComp"));
    SFXComp = CreateDefaultSubobject<UAudioComponent>(TEXT("SFXComp"));
}

void AGameOverHUD::BeginPlay()
{
    Super::BeginPlay();

    if (UserWidgetClass)
    {
        UserWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
        if (UserWidgetInstance)
        {
            UserWidgetInstance->AddToViewport();

            UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetOwningPlayerController(), UserWidgetInstance);

            UGameOverMenu* mainMenu = Cast<UGameOverMenu>(UserWidgetInstance);

            if (mainMenu) {
                mainMenu->UIPressHappened.AddUniqueDynamic(this, &AGameOverHUD::UIPressHappened);
            }
        }
    }
}

void AGameOverHUD::UIPressHappened() {
    SFXComp->Play();
}