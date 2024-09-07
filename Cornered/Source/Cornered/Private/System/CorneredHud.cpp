// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredHud.h"
#include "Blueprint/UserWidget.h"
#include "System/CorneredGameMode.h"
#include "Components/AudioComponent.h"
#include "Characters/Systems/CorneredCharacter.h"


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
    CorneredGameMode->CharacterDefeated.AddUniqueDynamic(this, &ACorneredHud::OnCharacterDefeated);
}

void ACorneredHud::OnTimerOverHappened() {
    BGMComp->Play();
    AmbientComp->Play();
}

void ACorneredHud::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {
    BGMComp->Stop();
    AmbientComp->Stop();
}