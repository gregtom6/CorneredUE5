// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorneredButton.h"
#include "Materials/MaterialInterface.h"
#include "ConveyorBeltSpeederButton.generated.h"

class UStaticMeshComponent;
class UConfig_Belt;
class ABeltController;

/**
 * 
 */
UCLASS()
class CORNERED_API AConveyorBeltSpeederButton : public ACorneredButton
{
	GENERATED_BODY()

public:

	AConveyorBeltSpeederButton();

	void Interact() override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> BeltButtonStaticMeshComp;
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
		UConfig_Belt* BeltConfig;

	UPROPERTY(EditAnywhere)
		ABeltController* BeltController;
};
