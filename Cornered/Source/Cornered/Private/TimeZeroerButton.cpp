// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "TimeZeroerButton.h"
#include "Components/StaticMeshComponent.h"
#include "CorneredGameMode.h"

ATimeZeroerButton::ATimeZeroerButton() {

	TimeButtonStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TimeButtonStaticMeshComp"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	TimeButtonStaticMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATimeZeroerButton::Interact() {
	Super::Interact();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	if (CorneredGameMode) {
		CorneredGameMode->ZeroingTimer();
	}
}