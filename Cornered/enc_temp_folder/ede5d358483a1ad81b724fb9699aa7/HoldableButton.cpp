// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Interactables/HoldableButton.h"
#include "Environment/Interactables/HoldActivable.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

// Sets default values
AHoldableButton::AHoldableButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AHoldableButton::HoldingStarted() {
	HoldActivable->HoldProcessStarted();

	if (ButtonReleaseComp) {
		ButtonReleaseComp->StopSequence();
	}

	if (ButtonPushComp) {
		ButtonPushComp->PlaySequence();
	}

	if (ButtonRotateComp) {
		ButtonRotateComp->GetSequencePlayer()->PlayLooping();
	}
}

void AHoldableButton::HoldingFinished() {
	HoldActivable->HoldProcessEnded();

	if (ButtonPushComp) {
		ButtonPushComp->StopSequence();
	}

	if (ButtonReleaseComp) {
		ButtonReleaseComp->PlaySequence();
	}

	if (ButtonRotateComp) {
		ButtonRotateComp->StopSequence();
		ButtonRotateComp->GetSequencePlayer()->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(0.0f, EUpdatePositionMethod::Jump));
	}
}