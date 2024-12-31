// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Others/LightBlinkController.h"
#include "Characters/Systems/CharacterSpawner.h"
#include "Curves/CurveFloat.h"

// Sets default values for this component's properties
ULightBlinkController::ULightBlinkController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightBlinkController::BeginPlay()
{
	Super::BeginPlay();

	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->OnSoulGenerated.AddUniqueDynamic(this, &ULightBlinkController::OnSoulEjected);
		MySubsystem->OnSoulDissipated.AddUniqueDynamic(this, &ULightBlinkController::OnSoulDissipated);
	}
	
}


// Called every frame
void ULightBlinkController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULightBlinkController::OnSoulEjected() {

}

void ULightBlinkController::OnSoulDissipated() {

}