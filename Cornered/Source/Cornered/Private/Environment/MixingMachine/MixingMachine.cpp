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
#include "Environment/MixingMachine/MixingMachineAbility.h"
#include "Environment/Interactables/CorneredButton.h"
#include "NiagaraSystem.h"
#include "Sound/SoundBase.h"


// Sets default values
AMixingMachine::AMixingMachine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	AbilityComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("AbilityComp"));
	ResultTarget = CreateDefaultSubobject<USceneComponent>(TEXT("ResultTarget"));
	AbilityAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("AbilityAudio"));
	CreationNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CreationNiagaraComp"));
	CreationAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("CreationAudio"));

	SetRootComponent(Root);
	ResultTarget->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	AbilityComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	AbilityAudio->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	CreationAudio->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	CreationNiagaraComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMixingMachine::BeginPlay()
{
	Super::BeginPlay();

	State = EMixingMachineState::Waiting;

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
	CorneredGameMode->NewMatchStarted.AddUniqueDynamic(this, &AMixingMachine::OnNewMatchStarted);

	GetComponents<UMixingMachineAbility>(AbilityComponents);

	for (int i = 0; i < AbilityComponents.Num(); i++) {
		AbilityComponents[i]->AbilityActivated.AddUniqueDynamic(this, &AMixingMachine::AbilityPressHappened);
	}
}

void AMixingMachine::AbilityTimeEnded() {
	State = EMixingMachineState::Waiting;

	if (TopLidOpenComp) {
		TopLidOpenComp->PlaySequence();
	}

	if (AbilityComp) {
		AbilityComp->Deactivate();
	}

	AbilityAudio->Stop();

	if (CurrentlyUsedAbility->IsThereCreationResult(MixingItemDetector, RecipeConfig)) {
		CreationNiagaraComp->Activate();
		CreationAudio->Play();
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::CreateResult, 0.1f, false);
}

void AMixingMachine::CreateResult() {
	CurrentlyUsedAbility->AbilityTimeEnded(MixingItemDetector, RecipeConfig, ResultTarget->GetComponentLocation());

	CurrentlyUsedAbility = nullptr;
}

void AMixingMachine::AbilityPressHappened(UMixingMachineAbility* SelectedAbility) {
	if (TopLidCloseComp) {
		TopLidCloseComp->PlaySequence();
	}

	State = EMixingMachineState::DoingProcess;

	CurrentlyUsedAbility = SelectedAbility;

	UNiagaraSystem* Niagara = CurrentlyUsedAbility->AbilityNiagara.LoadSynchronous();

	if (Niagara) {
		UNiagaraSystem* NiagaraSys = Cast<UNiagaraSystem>(Niagara);
		if (AbilityComp) {
			AbilityComp->SetAsset(NiagaraSys);
			AbilityComp->Activate(true);
		}
	}

	USoundBase* Sound = CurrentlyUsedAbility->AbilitySound.LoadSynchronous();
	if (Sound) {
		USoundBase* SoundActual = Cast<USoundBase>(Sound);
		if (AbilityAudio) {
			AbilityAudio->SetSound(SoundActual);
			AbilityAudio->Play();
		}
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMixingMachine::AbilityTimeEnded, CurrentlyUsedAbility->GetCurrentProcessTime(), false);
}

void AMixingMachine::OnNewMatchStarted() {

	for (int i = 0; i < AbilityComponents.Num(); i++) {
		AbilityComponents[i]->SetButtonStatus();
	}
}