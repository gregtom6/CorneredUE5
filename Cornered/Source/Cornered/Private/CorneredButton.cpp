// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CorneredButton.h"
#include "Components/AudioComponent.h"


// Sets default values
ACorneredButton::ACorneredButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PressAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PressAudio"));
}

void ACorneredButton::Interact() {

	PressAudio->Play();

	PressHappened.Broadcast();
}