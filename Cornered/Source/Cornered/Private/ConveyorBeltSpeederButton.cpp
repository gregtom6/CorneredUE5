// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ConveyorBeltSpeederButton.h"
#include "Components/StaticMeshComponent.h"
#include "Config_Belt.h"
#include "BeltController.h"

AConveyorBeltSpeederButton::AConveyorBeltSpeederButton() {

	BeltButtonStaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeltButtonStaticMeshComp"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);
	BeltButtonStaticMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void AConveyorBeltSpeederButton::BeginPlay() {

	UMaterialInterface* materialInstance= BeltConfig->GetMaterialBasedOnSpeed(BeltController->GetCurrentBeltSpeed());
	BeltButtonStaticMeshComp->SetMaterial(0, materialInstance);
}

void AConveyorBeltSpeederButton::Interact() {
	
	ACorneredButton::Interact();

	UMaterialInterface* materialInstance = BeltConfig->GetMaterialBasedOnSpeed(BeltController->GetCurrentBeltSpeed());
	BeltButtonStaticMeshComp->SetMaterial(0, materialInstance);
}