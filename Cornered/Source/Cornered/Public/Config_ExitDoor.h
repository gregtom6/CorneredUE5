// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_ExitDoor.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_ExitDoor : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		float ButtonHoldingOpenMultiplier;

	UPROPERTY(EditAnywhere)
		float MinPercentage;

	UPROPERTY(EditAnywhere)
		float MaxPercentage;
};
