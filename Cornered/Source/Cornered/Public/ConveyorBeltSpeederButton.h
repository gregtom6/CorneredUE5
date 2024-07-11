// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorneredButton.h"
#include "ConveyorBeltSpeederButton.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class CORNERED_API AConveyorBeltSpeederButton : public ACorneredButton
{
	GENERATED_BODY()

public:

	AConveyorBeltSpeederButton();

private:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> BeltButtonStaticMeshComp;
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;
};
