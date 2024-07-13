// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingMachine.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AMixingMachine::AMixingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BurningComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BurningComp"));

	FreezingComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FreezingComp"));

	SetRootComponent(Root);

	ResultTarget = CreateDefaultSubobject<USceneComponent>(TEXT("ResultTarget"));

	ResultTarget->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	BurningComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	FreezingComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMixingMachine::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorSequenceComponent*> ActorSequenceComponents;
	GetComponents<UActorSequenceComponent>(ActorSequenceComponents);

	for (int i = 0; i < ActorSequenceComponents.Num(); i++)
	{
		if (ActorSequenceComponents[i]->GetFName() == FName("TopLidSequence"))
		{
			TopLidSequence = ActorSequenceComponents[i];
		}
	}

}

// Called every frame
void AMixingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

