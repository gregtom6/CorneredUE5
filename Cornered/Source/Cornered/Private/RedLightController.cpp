// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#include "RedLightController.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "CorneredGameMode.h"
#include "GameFramework/Character.h"


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
	
}

void ARedLightController::OnTimerOverHappened()
{
	// Your code here
	UE_LOG(LogTemp, Warning, TEXT("TimerFunction has been called!"));

	TArray<UActorSequenceComponent*> ActorSequenceComponents;
	GetComponents<UActorSequenceComponent>(ActorSequenceComponents);

	for (int i = 0; i < ActorSequenceComponents.Num(); i++)
	{
		if (ActorSequenceComponents[i]->GetFName() == FName("DefaultDisabledSequence"))
		{
			DisabledSequ = ActorSequenceComponents[i];
		}
		else if (ActorSequenceComponents[i]->GetFName() == FName("BlinkingSequence"))
		{
			BlinkingSequ = ActorSequenceComponents[i];
		}
	}

	UActorSequencePlayer* stpper = DisabledSequ->GetSequencePlayer();
	if (stpper) {
		stpper->Stop();
	}

	UActorSequencePlayer* player = BlinkingSequ->GetSequencePlayer();
	if (player) {
		player->PlayLooping();
	}
}

void ARedLightController::OnCharacterDefeated(ACharacter* DefeatedCharacter) {
	UActorSequencePlayer* player = BlinkingSequ->GetSequencePlayer();
	if (player) {
		player->Stop();
	}

	UActorSequencePlayer* stpper = DisabledSequ->GetSequencePlayer();
	if (stpper) {
		stpper->Play();
	}
}