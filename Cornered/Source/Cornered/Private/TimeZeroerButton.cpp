// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeZeroerButton.h"
#include "Components/StaticMeshComponent.h"

ATimeZeroerButton::ATimeZeroerButton() {

	TimeButtonStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TimeButtonStaticMeshComp"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	TimeButtonStaticMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}