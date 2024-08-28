// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/ConveyorBelt/BeltElement.h"
#include "Environment/ConveyorBelt/BeltController.h"
#include "Configs/DataAssets/Config_IngredientGeneration.h"
#include "Items/Ingredient.h"

ABeltElement::ABeltElement()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ItemPivot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemPivot"));

	SetRootComponent(Root);
	ItemPivot->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

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

		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABeltElement::TimerFunction, 0.001f, false);
	}
}

void ABeltElement::TimerFunction() {
	TSubclassOf<AIngredient> ingredient = IngredientGenConfig->GetWeightedRandomItemClass();

	UWorld* world = GetWorld();

	if (ingredient && ItemPivot) {
		FVector pos = ItemPivot->GetComponentLocation();
		FVector WorldPosition = GetTransform().TransformPosition(pos);
		GetWorld()->SpawnActor<AActor>(ingredient, ItemPivot->GetComponentLocation(), FRotator::ZeroRotator);
	}
}