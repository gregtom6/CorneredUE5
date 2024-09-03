// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Gates/GateController.h"
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
	
	EnterDetectorComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGateController::OnEnterDetectorBeginOverlap);
	ExitDetectorComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGateController::OnExitDetectorBeginOverlap);
}

void AGateController::OnEnterDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (OpenSequ) {
		OpenSequ->PlaySequence();
	}
}

void AGateController::OnExitDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	if (CloseSequ) {
		CloseSequ->PlaySequence();
	}
}