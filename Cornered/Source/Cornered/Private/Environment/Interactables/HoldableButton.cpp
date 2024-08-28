// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "HoldableButton.h"
#include "HoldActivable.h"

// Sets default values
AHoldableButton::AHoldableButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AHoldableButton::HoldingStarted() {
	HoldActivable->HoldProcessStarted();
}

void AHoldableButton::HoldingFinished() {
	HoldActivable->HoldProcessEnded();
}