// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "HoldActivable.h"

// Sets default values
AHoldActivable::AHoldActivable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHoldActivable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoldActivable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

