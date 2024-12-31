// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Others/LightBlinkController.h"
#include "Characters/Systems/CharacterSpawner.h"
#include "Environment/Others/LightBlinkable.h"
#include "Components/LightComponent.h"
#include "Configs/DataAssets/Config_Soul.h"
#include "Materials/MaterialInstanceDynamic.h"

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

	ILightBlinkable* InterfaceInstance = Cast<ILightBlinkable>(GetOwner());
	if (InterfaceInstance)
	{
		Lights = InterfaceInstance->GetLightComponents();

		for (int i = 0; i < Lights.Num(); i++) {
			OriginalIntensities.Add(Lights[i]->Intensity);
		}

		LightMaterials = InterfaceInstance->GetLightMaterials();
	}

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

	if (!bIsSoulExisting) {
		return;
	}

	float IntensityMultiplier = SoulConfig->GetIntensityMultiplier(Time);
	Time += DeltaTime * SoulConfig->CurveReadMultiplier;
	if (Time >= 1.f) {
		Time = 0.f;
	}

	for (int i = 0; i < Lights.Num(); i++) {
		if (i < OriginalIntensities.Num()) {
			Lights[i]->Intensity = IntensityMultiplier * OriginalIntensities[i];
		}
	}

	for (int i = 0; i < LightMaterials.Num(); i++) {
		LightMaterials[i]->SetScalarParameterValue(FName("ColorMultiplier"), IntensityMultiplier/1000.0f);

	}
}

void ULightBlinkController::OnSoulEjected() {
	bIsSoulExisting = true;
	Time = FMath::RandRange(0.f, 1.f);
}

void ULightBlinkController::OnSoulDissipated() {
	bIsSoulExisting = false;
	for (int i = 0; i < Lights.Num(); i++) {
		if (i < OriginalIntensities.Num()) {
			Lights[i]->Intensity = OriginalIntensities[i];
		}
	}

	for (int i = 0; i < LightMaterials.Num(); i++) {
		LightMaterials[i]->SetScalarParameterValue(FName("ColorMultiplier"), 1.f);
	}
}