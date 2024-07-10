// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Belt.generated.h"

UENUM()
enum class EBeltSpeed : uint8 {
	Normal,
	Fastened,

	Count,
};


class ABeltElement;
/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Belt : public UDataAsset
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
		float NormalMultiplier;
	UPROPERTY(EditAnywhere)
		float SpeedMultiplier;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABeltElement> BeltElementClass;

public:

	UFUNCTION()
		float GetCurrentMultiplier(EBeltSpeed beltSpeed);

	UFUNCTION()
		TSubclassOf<ABeltElement> GetBeltElementClass();
};
