// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/ExitDoor/ExitButtonMover.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

// Sets default values
AExitButtonMover::AExitButtonMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);
}

void AExitButtonMover::StartMoving() {
	if (OpenSequ) {
		OpenSequ->PlaySequence();
	}
}