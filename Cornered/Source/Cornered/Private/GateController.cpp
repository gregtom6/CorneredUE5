// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "GateController.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

// Sets default values
AGateController::AGateController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GateVisualsParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("GateVisualsParentComp"));

	EnterDetectorParentComp= CreateDefaultSubobject<USceneComponent>(TEXT("EnterDetectorParentComp"));

	ExitDetectorParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("ExitDetectorParentComp"));

	EnterDetectorComp = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterDetectorComp"));

	ExitDetectorComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ExitDetectorComp"));

	SetRootComponent(Root);

	GateVisualsParentComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	EnterDetectorParentComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	ExitDetectorParentComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	EnterDetectorComp->AttachToComponent(EnterDetectorParentComp, FAttachmentTransformRules::KeepRelativeTransform);

	ExitDetectorComp->AttachToComponent(ExitDetectorParentComp, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AGateController::BeginPlay()
{
	Super::BeginPlay();
	
	EnterDetectorComp->OnComponentBeginOverlap.AddDynamic(this, &AGateController::OnEnterDetectorBeginOverlap);

	ExitDetectorComp->OnComponentBeginOverlap.AddDynamic(this, &AGateController::OnExitDetectorBeginOverlap);

	TArray<UActorSequenceComponent*> ActorSequenceComponents;
	GetComponents<UActorSequenceComponent>(ActorSequenceComponents);

	for (int i = 0; i < ActorSequenceComponents.Num(); i++)
	{
		if (ActorSequenceComponents[i]->GetFName() == FName("OpenSequence"))
		{
			OpenSequ = ActorSequenceComponents[i];
		}
		else if (ActorSequenceComponents[i]->GetFName() == FName("CloseSequence"))
		{
			CloseSequ = ActorSequenceComponents[i];
		}
	}
}

void AGateController::OnEnterDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	UActorSequencePlayer* player = OpenSequ->GetSequencePlayer();
	if (player) {
		player->Play();
	}
}

void AGateController::OnExitDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	UActorSequencePlayer* player = CloseSequ->GetSequencePlayer();
	if (player) {
		player->Play();
	}
}