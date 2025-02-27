// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Interactables/TimeZeroerButton.h"
#include "Components/StaticMeshComponent.h"
#include "System/CorneredGameMode.h"

ATimeZeroerButton::ATimeZeroerButton() {

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TimeButtonStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TimeButtonStaticMeshComp"));

	SetRootComponent(Root);
	TimeButtonStaticMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATimeZeroerButton::Interact() {

	if (SelfState == ETimerButtonState::Deactivated) {
		return;
	}

	Super::Interact();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	if (CorneredGameMode) {
		CorneredGameMode->ZeroingTimer();
	}
}

void ATimeZeroerButton::BeginPlay()
{
	Super::BeginPlay();

	ManageButton(ETimerButtonState::Activated);

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	CorneredGameMode->TimeOverHappened.AddUniqueDynamic(this, &ATimeZeroerButton::OnTimerOverHappened);
	CorneredGameMode->NewMatchStarted.AddUniqueDynamic(this, &ATimeZeroerButton::OnNewMatchStarted);
}

void ATimeZeroerButton::OnTimerOverHappened()
{
	ManageButton(ETimerButtonState::Deactivated);
}

void ATimeZeroerButton::OnNewMatchStarted() {
	ManageButton(ETimerButtonState::Activated);
}

void ATimeZeroerButton::ManageButton(ETimerButtonState State) {

	SelfState = State;

	UMaterialInterface* materialInstance = OthersConfig->GetMaterialBasedOnState(State);
	TimeButtonStaticMeshComp->SetMaterial(0, materialInstance);
}