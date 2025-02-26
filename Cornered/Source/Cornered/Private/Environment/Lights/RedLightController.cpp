// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#include "Environment/Lights/RedLightController.h"
#include "System/CorneredGameMode.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "System/ProgressionGameState.h"

// Sets default values
ARedLightController::ARedLightController()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARedLightController::BeginPlay()
{
	Super::BeginPlay();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
	AGameStateBase* GameState = GetWorld()->GetGameState();
	AProgressionGameState* ProgressionGameState = Cast<AProgressionGameState>(GameState);

	CorneredGameMode->TimeOverHappened.AddUniqueDynamic(this, &ARedLightController::OnTimerOverHappened);
	ProgressionGameState->CharacterDefeated.AddUniqueDynamic(this, &ARedLightController::OnCharacterDefeated);

	if (SequenceComp) {
		SequenceComp->StopSequence();
	}

	if (DisabledSequComp) {
		DisabledSequComp->PlaySequence();
	}
}

void ARedLightController::OnTimerOverHappened()
{
	if (DisabledSequComp) {
		DisabledSequComp->StopSequence();
	}

	if (SequenceComp) {
		UActorSequencePlayer* riot = SequenceComp->GetSequencePlayer();
		if (riot) {
			riot->PlayLooping();
		}
	}
}

void ARedLightController::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {

	if (DefeatedCharacter->IsA<APlayerCharacter>()) {
		return;
	}

	if (SequenceComp) {
		SequenceComp->StopSequence();
	}

	if (DisabledSequComp) {
		DisabledSequComp->PlaySequence();
	}
}