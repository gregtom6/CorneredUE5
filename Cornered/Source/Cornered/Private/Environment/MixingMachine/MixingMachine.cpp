// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/MixingMachine/MixingMachine.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Configs/DataAssets/Config_MixingMachine.h"
#include "Environment/MixingMachine/MixingItemDetector.h"
#include "Items/Ingredient.h"
#include "Configs/DataAssets/Config_Recipe.h"
#include "Components/AudioComponent.h"
#include "System/ProgressionGameState.h"
#include "System/CorneredGameMode.h"

// Sets default values
AMixingMachine::AMixingMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BurningComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BurningComp"));
	FreezingComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FreezingComp"));
	ResultTarget = CreateDefaultSubobject<USceneComponent>(TEXT("ResultTarget"));
	BurnAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BurnAudio"));
	FreezeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("FreezeAudio"));
	MixingAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MixingAudio"));

	SetRootComponent(Root);
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

	State = EMixingMachineState::Waiting;

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	ConvertButton->PressHappened.AddUniqueDynamic(this, &AMixingMachine::ConvertPressHappened);
	BurnButton->PressHappened.AddUniqueDynamic(this, &AMixingMachine::BurnPressHappened);
	FreezeButton->PressHappened.AddUniqueDynamic(this, &AMixingMachine::FreezePressHappened);
	CorneredGameMode->NewMatchStarted.AddUniqueDynamic(this, &AMixingMachine::OnNewMatchStarted);
}

void AMixingMachine::ConvertPressHappened() {
	
	if (TopLidCloseComp) {
		TopLidCloseComp->PlaySequence();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::ConvertTimeEnded, GetCurrentProcessTime(EAbility::Default), false);

	State = EMixingMachineState::DoingProcess;

	MixingAudio->Play();
}


void AMixingMachine::ConvertTimeEnded() {
	State = EMixingMachineState::Waiting;

	if (TopLidOpenComp) {
		TopLidOpenComp->PlaySequence();
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

	if (TopLidOpenComp) {
		TopLidOpenComp->PlaySequence();
	}

	if (BurningComp) {
		BurningComp->Deactivate();
	}

	MixingItemDetector->BurnAllItems();

	BurnAudio->Stop();
}

void AMixingMachine::FreezeTimeEnded() {
	State = EMixingMachineState::Waiting;

	if (TopLidOpenComp) {
		TopLidOpenComp->PlaySequence();
	}

	if (FreezingComp) {
		FreezingComp->Deactivate();
	}

	MixingItemDetector->FreezeAllItems();

	FreezeAudio->Stop();
}

void AMixingMachine::BurnPressHappened() {
	if (TopLidCloseComp) {
		TopLidCloseComp->PlaySequence();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::BurnTimeEnded, GetCurrentProcessTime(EAbility::Burn), false);

	State = EMixingMachineState::DoingProcess;

	if (BurningComp) {
		BurningComp->Activate(true);
	}

	BurnAudio->Play();
}

void AMixingMachine::FreezePressHappened() {
	if (TopLidCloseComp) {
		TopLidCloseComp->PlaySequence();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::FreezeTimeEnded, GetCurrentProcessTime(EAbility::Freeze), false);

	State = EMixingMachineState::DoingProcess;

	if (FreezingComp) {
		FreezingComp->Activate(true);
	}

	FreezeAudio->Play();
}

float AMixingMachine::GetCurrentProcessTime(EAbility ability) const {
	return MixingMachineConfig->GetProcessTime(ability);
}

void AMixingMachine::OnNewMatchStarted() {

	AProgressionGameState* GameState = GetWorld()->GetGameState<AProgressionGameState>();

	ConvertButton->SetActorHiddenInGame(!GameState->IsAbilityAlreadyUnlocked(EAbility::Default));
	BurnButton->SetActorHiddenInGame(!GameState->IsAbilityAlreadyUnlocked(EAbility::Burn));
	FreezeButton->SetActorHiddenInGame(!GameState->IsAbilityAlreadyUnlocked(EAbility::Freeze));
}