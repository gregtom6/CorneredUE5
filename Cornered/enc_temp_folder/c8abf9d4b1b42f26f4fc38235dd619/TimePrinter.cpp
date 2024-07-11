// Fill out your copyright notice in the Description page of Project Settings.


#include "TimePrinter.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ATimePrinter::ATimePrinter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	TimeLeftComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TimeLeftComp"));

	TimeLeftComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ATimePrinter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimePrinter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

