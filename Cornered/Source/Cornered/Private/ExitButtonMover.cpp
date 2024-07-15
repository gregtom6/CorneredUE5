// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ExitButtonMover.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

// Sets default values
AExitButtonMover::AExitButtonMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AExitButtonMover::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorSequenceComponent*> ActorSequenceComponents;
	GetComponents<UActorSequenceComponent>(ActorSequenceComponents);

	for (int i = 0; i < ActorSequenceComponents.Num(); i++)
	{
		if (ActorSequenceComponents[i]->GetFName() == FName("OpenSequence"))
		{
			OpenSequ = ActorSequenceComponents[i];
		}
	}
}

// Called every frame
void AExitButtonMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExitButtonMover::StartMoving() {
	UActorSequencePlayer* player = OpenSequ->GetSequencePlayer();
	if (player) {
		player->Play();
	}
}