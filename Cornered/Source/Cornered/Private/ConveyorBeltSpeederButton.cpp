// Fill out your copyright notice in the Description page of Project Settings.


#include "ConveyorBeltSpeederButton.h"
#include "Components/StaticMeshComponent.h"

AConveyorBeltSpeederButton::AConveyorBeltSpeederButton() {

	BeltButtonStaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BeltButtonStaticMeshComp"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	BeltButtonStaticMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}