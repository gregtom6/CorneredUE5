// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/InteractableDetector.h"

UInteractableDetector::UInteractableDetector()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bTickEvenWhenPaused = true;
}

void UInteractableDetector::BeginPlay()
{
	Super::BeginPlay();

	CachedWorld = GetWorld();
}

void UInteractableDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector origin = GetComponentLocation();
	FTransform ComponentTransform = GetComponentTransform();
	FVector LocalRightVector = ComponentTransform.GetUnitAxis(EAxis::X);

	float rayLength = 900.0f;

	bIsValidHit = CachedWorld->LineTraceSingleByChannel(HitResult, origin, origin + LocalRightVector * rayLength, ECC_Visibility);
}

bool UInteractableDetector::ItWasValidHit() const {
	return bIsValidHit;
}

FHitResult UInteractableDetector::GetHitResult() const {
	return HitResult;
}