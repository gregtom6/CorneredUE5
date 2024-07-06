// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDetector.h"

// Sets default values for this component's properties
UInteractableDetector::UInteractableDetector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bTickEvenWhenPaused = true;
	// ...
}


// Called when the game starts
void UInteractableDetector::BeginPlay()
{
	Super::BeginPlay();

	CachedWorld = GetWorld();

}


// Called every frame
void UInteractableDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector origin = GetComponentLocation();
	FTransform ComponentTransform = GetComponentTransform();
	FVector LocalRightVector = ComponentTransform.GetUnitAxis(EAxis::X);

	float rayLength = 900.0f;

	bIsValidHit = CachedWorld->LineTraceSingleByChannel(HitResult, origin, origin + LocalRightVector * rayLength, ECC_Visibility);

#if WITH_EDITOR
	/*
	DrawDebugLine(
		CachedWorld,
		origin,
		origin + LocalRightVector * rayLength,
		FColor::Green,
		false,
		1.0f,
		0,
		1.0f
	);
	*/

#endif
}

bool UInteractableDetector::ItWasValidHit() {
	return bIsValidHit;
}

FHitResult UInteractableDetector::GetHitResult() {
	return HitResult;
}