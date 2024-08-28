// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#include "RedLightController.h"
#include "CorneredGameMode.h"
#include "GameFramework/Character.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

// Sets default values
ARedLightController::ARedLightController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ARedLightController::BeginPlay()
{
	Super::BeginPlay();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	CorneredGameMode->TimeOverHappened.AddUniqueDynamic(this, &ARedLightController::OnTimerOverHappened);
	CorneredGameMode->CharacterDefeated.AddDynamic(this, &ARedLightController::OnCharacterDefeated);

	if (SequenceComp) {
		SequenceComp->StopSequence();
	}

	if (DisabledSequComp) {
		DisabledSequComp->PlaySequence();
	}
}

void ARedLightController::OnTimerOverHappened()
{
	UE_LOG(LogTemp, Warning, TEXT("TimerFunction has been called!"));

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

void ARedLightController::OnCharacterDefeated(ACharacter* DefeatedCharacter) {

	if (SequenceComp) {
		SequenceComp->StopSequence();
	}

	if (DisabledSequComp) {
		DisabledSequComp->PlaySequence();
	}
}