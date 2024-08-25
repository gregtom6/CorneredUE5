// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#include "RedLightController.h"
#include "CorneredGameMode.h"
#include "GameFramework/Character.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

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
	

	if (!BlinkingSequenceAsset.IsValid())
	{
		BlinkingSequenceAsset.LoadSynchronous();
	}

	ULevelSequence* LevelSequence = BlinkingSequenceAsset.Get();

	if (LevelSequence)
	{
		FMovieSceneSequencePlaybackSettings PlaybackSettings;

		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			LevelSequence,
			PlaybackSettings,
			LevelSequenceActor
		);

		if (LevelSequencePlayer)
		{
			LevelSequencePlayer->Stop();
		}
	}
}

void ARedLightController::OnTimerOverHappened()
{
	UE_LOG(LogTemp, Warning, TEXT("TimerFunction has been called!"));

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->PlayLooping();
	}
}

void ARedLightController::OnCharacterDefeated(ACharacter* DefeatedCharacter) {

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->Stop();
	}
}