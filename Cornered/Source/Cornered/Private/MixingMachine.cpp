// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingMachine.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Config_MixingMachine.h"
#include "MixingItemDetector.h"
#include "Ingredient.h"
#include "Config_Recipe.h"
#include "Components/AudioComponent.h"

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

	BurnAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BurnAudio"));

	FreezeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("FreezeAudio"));

	MixingAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MixingAudio"));

	ResultTarget->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	BurningComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	FreezingComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	BurnAudio->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	FreezeAudio->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	MixingAudio->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMixingMachine::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorSequenceComponent*> ActorSequenceComponents;
	GetComponents<UActorSequenceComponent>(ActorSequenceComponents);

	for (int i = 0; i < ActorSequenceComponents.Num(); i++)
	{
		if (ActorSequenceComponents[i]->GetFName() == FName("TopLidOpen"))
		{
			TopLidOpenComp = ActorSequenceComponents[i];
		}
		else if (ActorSequenceComponents[i]->GetFName() == FName("TopLidClose"))
		{
			TopLidCloseComp = ActorSequenceComponents[i];
		}
	}

	State = EMixingMachineState::Waiting;

	ConvertButton->PressHappened.AddUniqueDynamic(this, &AMixingMachine::ConvertPressHappened);
	BurnButton->PressHappened.AddUniqueDynamic(this, &AMixingMachine::BurnPressHappened);
	FreezeButton->PressHappened.AddUniqueDynamic(this, &AMixingMachine::FreezePressHappened);
}

void AMixingMachine::ConvertPressHappened() {
	
	UActorSequencePlayer* player = TopLidCloseComp->GetSequencePlayer();
	if (player) {
		player->Play();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::ConvertTimeEnded, GetCurrentProcessTime(EAbility::Default), false);

	State = EMixingMachineState::DoingProcess;

	MixingAudio->Play();
}


void AMixingMachine::ConvertTimeEnded() {
	State = EMixingMachineState::Waiting;

	UActorSequencePlayer* player = TopLidOpenComp->GetSequencePlayer();
	if (player) {
		player->Play();
	}

	TArray<FItemData> detectedItems = MixingItemDetector->GetDetectedItems();

	if (detectedItems.Num() == 0)
	{
		return;
	}

	TSubclassOf<AIngredient> result = RecipeConfig->GetResultItem(detectedItems);

	if (result)
	{
		GetWorld()->SpawnActor<AActor>(result, ResultTarget->GetComponentLocation(), FRotator::ZeroRotator);
		MixingItemDetector->DestroyAllItems();
	}

	MixingAudio->Stop();
}

void AMixingMachine::BurnTimeEnded() {
	State = EMixingMachineState::Waiting;

	UActorSequencePlayer* player = TopLidOpenComp->GetSequencePlayer();
	if (player) {
		player->Play();
	}

	if (BurningComp) {
		BurningComp->Deactivate();
	}

	MixingItemDetector->BurnAllItems();

	BurnAudio->Stop();
}

void AMixingMachine::FreezeTimeEnded() {
	State = EMixingMachineState::Waiting;

	UActorSequencePlayer* player = TopLidOpenComp->GetSequencePlayer();
	if (player) {
		player->Play();
	}

	if (FreezingComp) {
		FreezingComp->Deactivate();
	}

	MixingItemDetector->FreezeAllItems();

	FreezeAudio->Stop();
}

void AMixingMachine::BurnPressHappened() {
	UActorSequencePlayer* player = TopLidCloseComp->GetSequencePlayer();
	if (player) {
		player->Play();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::BurnTimeEnded, GetCurrentProcessTime(EAbility::Burn), false);

	State = EMixingMachineState::DoingProcess;

	if (BurningComp) {
		BurningComp->Activate(true);
	}

	BurnAudio->Play();
}

void AMixingMachine::FreezePressHappened() {
	UActorSequencePlayer* player = TopLidCloseComp->GetSequencePlayer();
	if (player) {
		player->Play();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::FreezeTimeEnded, GetCurrentProcessTime(EAbility::Freeze), false);

	State = EMixingMachineState::DoingProcess;

	if (FreezingComp) {
		FreezingComp->Activate(true);
	}

	FreezeAudio->Play();
}

// Called every frame
void AMixingMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


float AMixingMachine::GetCurrentProcessTime(EAbility ability) {
	return MixingMachineConfig->GetProcessTime(ability);
}
