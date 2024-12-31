// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredHud.h"
#include "Blueprint/UserWidget.h"
#include "System/CorneredGameMode.h"
#include "Components/AudioComponent.h"
#include "System/ProgressionGameState.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "Characters/Systems/CharacterSpawner.h"


ACorneredHud::ACorneredHud() {
    BGMComp = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMComp"));
    AmbientComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientComp"));
    StaticNoiseComp = CreateDefaultSubobject<UAudioComponent>(TEXT("StaticNoiseComp"));
    LightFlickerComp = CreateDefaultSubobject<UAudioComponent>(TEXT("LightFlickerComp"));
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

    AGameStateBase* GameState = GetWorld()->GetGameState();
    AProgressionGameState* ProgressionGameState = Cast<AProgressionGameState>(GameState);

    ProgressionGameState->CharacterDefeated.AddUniqueDynamic(this, &ACorneredHud::OnCharacterDefeated);

    UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
    if (MySubsystem)
    {
        MySubsystem->OnSoulGenerated.AddUniqueDynamic(this, &ACorneredHud::OnSoulEjected);
        MySubsystem->OnSoulDissipated.AddUniqueDynamic(this, &ACorneredHud::OnSoulDissipated);
    }
}

void ACorneredHud::OnTimerOverHappened() {
    BGMComp->Play();
    AmbientComp->Play();
}

void ACorneredHud::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {
    BGMComp->Stop();
    AmbientComp->Stop();
}

void ACorneredHud::OnSoulEjected() {
    StaticNoiseComp->FadeIn(1.f,1.f);
    LightFlickerComp->Play(1.f);
}

void ACorneredHud::OnSoulDissipated() {
    StaticNoiseComp->FadeOut(1.f, 0.f);
    LightFlickerComp->StopDelayed(1.f);
}