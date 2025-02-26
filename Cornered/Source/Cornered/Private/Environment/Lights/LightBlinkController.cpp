// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Lights/LightBlinkController.h"
#include "Characters/Systems/CharacterSpawner.h"
#include "Environment/Lights/LightBlinkable.h"
#include "Components/LightComponent.h"
#include "Configs/DataAssets/Config_Soul.h"
#include "Materials/MaterialInstanceDynamic.h"

const FName ULightBlinkController::ColorMultiplier(TEXT("ColorMultiplier"));

// Sets default values for this component's properties
ULightBlinkController::ULightBlinkController()
{
	PrimaryComponentTick.bCanEverTick = true;
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
			Lights[i]->SetIntensity(IntensityMultiplier * OriginalIntensities[i]);
		}
	}

	for (int i = 0; i < LightMaterials.Num(); i++) {
		if (LightMaterials[i]) {

			LightMaterials[i]->SetScalarParameterValue(ColorMultiplier, IntensityMultiplier);
		}

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
			Lights[i]->SetIntensity(OriginalIntensities[i]);
		}
	}

	for (int i = 0; i < LightMaterials.Num(); i++) {
		if (LightMaterials[i]) {
			LightMaterials[i]->SetScalarParameterValue(ColorMultiplier, 1.f);
		}
	}
}