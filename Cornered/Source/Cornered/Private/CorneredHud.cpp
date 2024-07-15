// Fill out your copyright notice in the Description page of Project Settings.


#include "CorneredHud.h"
#include "Blueprint/UserWidget.h"
#include "CorneredGameMode.h"
#include "Components/AudioComponent.h"

ACorneredHud::ACorneredHud() {
    BGMComp = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMComp"));
    AmbientComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientComp"));
}

void ACorneredHud::BeginPlay()
{
    Super::BeginPlay();

    for (TSubclassOf<UUserWidget> WidgetClass : WidgetClasses)
    {
        if (WidgetClass)
        {
            // Create the widget and add it to the viewport
            UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
            if (WidgetInstance)
            {
                WidgetInstance->AddToViewport();
                WidgetInstances.Add(WidgetInstance);
            }
        }
    }

    ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

    CorneredGameMode->TimeOverHappened.AddUniqueDynamic(this, &ACorneredHud::OnTimerOverHappened);
}

void ACorneredHud::OnTimerOverHappened() {
    BGMComp->Play();
    AmbientComp->Play();
}