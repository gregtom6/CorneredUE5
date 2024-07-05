// Fill out your copyright notice in the Description page of Project Settings.


#include "CorneredHud.h"
#include "Blueprint/UserWidget.h"

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
}