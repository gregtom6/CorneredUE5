// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/ExitDoor/ExitDoorController.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "Configs/DataAssets/Config_ExitDoor.h"
#include "Environment/Interactables/HoldableButton.h"
#include "Environment/ExitDoor/ExitButtonMover.h"

AExitDoorController::AExitDoorController() {

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	DoorVisuals = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorVisuals"));
	PercentageText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PercentageText"));
	ProgressText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ProgressText"));

	SetRootComponent(Root);
	DoorVisuals->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	PercentageText->AttachToComponent(DoorVisuals, FAttachmentTransformRules::KeepRelativeTransform);
	ProgressText->AttachToComponent(DoorVisuals, FAttachmentTransformRules::KeepRelativeTransform);
}

void AExitDoorController::BeginPlay()
{
	Super::BeginPlay();

	PrintPercentageText();

	HoldableButton->AttachToActor(ExitButtonParent, FAttachmentTransformRules::KeepWorldTransform);
}

void AExitDoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bOpeningInProgress) {
		return;
	}

	OpeningPercentage += ExitDoorConfig->ButtonHoldingOpenMultiplier * DeltaTime;
	OpeningPercentage = FMath::Clamp(OpeningPercentage, ExitDoorConfig->MinPercentage, ExitDoorConfig->MaxPercentage);

	PrintPercentageText();

	if (OpeningPercentage>= ExitDoorConfig->MaxPercentage && !bDoorOpened) {
		if (OpenSequ) {
			OpenSequ->PlaySequence();

			ExitButtonParent->StartMoving();

			bDoorOpened = true;
		}
	}
}

void AExitDoorController::HoldProcessStarted() {
	bOpeningInProgress = true;
}

void AExitDoorController::HoldProcessEnded() {
	bOpeningInProgress = false;
}

void AExitDoorController::PrintPercentageText() {
	int32 IntValue = FMath::RoundToInt(OpeningPercentage);

	FString stringVersion = FString::FromInt(IntValue);

	PercentageText->SetText(FText::FromString(stringVersion));
}