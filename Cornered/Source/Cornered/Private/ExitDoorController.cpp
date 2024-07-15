// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ExitDoorController.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "Config_ExitDoor.h"
#include "HoldableButton.h"
#include "ExitButtonMover.h"

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

	TArray<UActorSequenceComponent*> ActorSequenceComponents;
	GetComponents<UActorSequenceComponent>(ActorSequenceComponents);

	for (int i = 0; i < ActorSequenceComponents.Num(); i++)
	{
		if (ActorSequenceComponents[i]->GetFName() == FName("OpenSequence"))
		{
			OpenSequ = ActorSequenceComponents[i];
		}
	}

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
		UActorSequencePlayer* player = OpenSequ->GetSequencePlayer();
		if (player) {
			player->Play();

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