// Fill out your copyright notice in the Description page of Project Settings.


#include "BeltElement.h"
#include "BeltController.h"
#include "Config_IngredientGeneration.h"
#include "Ingredient.h"

// Sets default values
ABeltElement::ABeltElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	ItemPivot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemPivot"));

	ItemPivot->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ABeltElement::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABeltElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float currentBeltSpeed = BeltController->GetCurrentMultiplier();

	FVector NewLocation = GetActorLocation() + (currentBeltSpeed * DeltaTime * GetActorForwardVector());
	SetActorLocation(NewLocation);
}

void ABeltElement::SetBeltController(ABeltController* controller) {
	BeltController = controller;
}

void ABeltElement::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);

	if (!bNewHidden) {

		//TODO: remove timer and use a function which gets called, when GetComponentLocation already gives back world coordinates instead of local. 
		//tried in BeginPlay, tried in PostInitializeComponents, in both of them GetComponentLocation was invalid, probably because of the Object Pool

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABeltElement::TimerFunction, 3.0f, false);
	}
}

void ABeltElement::TimerFunction() {
	TSubclassOf<AIngredient> ingredient = IngredientGenConfig->GetWeightedRandomItemClass();

	UWorld* world = GetWorld();

	if (ingredient && ItemPivot && this) {
		FVector pos = ItemPivot->GetComponentLocation();
		FVector WorldPosition = GetTransform().TransformPosition(pos);
		GetWorld()->SpawnActor<AActor>(ingredient, ItemPivot->GetComponentLocation(), FRotator::ZeroRotator);
	}
}