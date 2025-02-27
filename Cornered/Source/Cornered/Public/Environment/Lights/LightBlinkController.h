// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LightBlinkController.generated.h"

class UCurveFloat;
class ULightComponent;
class UConfig_Soul;
class UMaterialInstanceDynamic;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API ULightBlinkController : public UActorComponent
{
	GENERATED_BODY()

private:

	static const FName ColorMultiplier;

	bool bIsSoulExisting;

	float Time;

	TArray<float> OriginalIntensities;

	UPROPERTY()
	TArray<TObjectPtr<ULightComponent>> Lights;

	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> LightMaterials;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Soul> SoulConfig;

public:	
	ULightBlinkController();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnSoulEjected();

	UFUNCTION()
	void OnSoulDissipated();

};
