// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Interactables/ConveyorBeltSpeederButton.h"
#include "Components/StaticMeshComponent.h"
#include "Configs/DataAssets/Config_Belt.h"
#include "Environment/ConveyorBelt/BeltController.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

AConveyorBeltSpeederButton::AConveyorBeltSpeederButton() {

	BeltButtonStaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeltButtonStaticMeshComp"));
	ButtonHolderStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonHolderStaticMeshComp"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);
	ButtonHolderStaticMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	BeltButtonStaticMeshComp->AttachToComponent(ButtonHolderStaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
}

void AConveyorBeltSpeederButton::BeginPlay() {

	Super::BeginPlay();

	SetMaterialBasedOnSpeed();
}

void AConveyorBeltSpeederButton::Interact() {
	
	ACorneredButton::Interact();

	SetMaterialBasedOnSpeed();
}

void AConveyorBeltSpeederButton::SetMaterialBasedOnSpeed() {
	UMaterialInterface* materialInstance = BeltConfig->GetMaterialBasedOnSpeed(BeltController->GetCurrentBeltSpeed());
	BeltButtonStaticMeshComp->SetMaterial(0, materialInstance);
}