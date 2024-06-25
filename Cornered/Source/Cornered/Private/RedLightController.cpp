// Fill out your copyright notice in the Description page of Project Settings.

#include "RedLightController.h"
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

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARedLightController::TimerFunction, 5.0f, false);

	
}

void ARedLightController::TimerFunction()
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

	UActorSequencePlayer* player = BlinkingSequ->GetSequencePlayer();
	if (player) {
		player->Play();
	}
}

// Called every frame
void ARedLightController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

