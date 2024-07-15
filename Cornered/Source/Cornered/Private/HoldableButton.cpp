// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "HoldableButton.h"
#include "HoldActivable.h"

// Sets default values
AHoldableButton::AHoldableButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHoldableButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoldableButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHoldableButton::HoldingStarted() {
	HoldActivable->HoldProcessStarted();
}

void AHoldableButton::HoldingFinished() {
	HoldActivable->HoldProcessEnded();
}