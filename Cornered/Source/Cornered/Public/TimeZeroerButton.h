// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorneredButton.h"
#include "TimeZeroerButton.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class CORNERED_API ATimeZeroerButton : public ACorneredButton
{
	GENERATED_BODY()

public:
		ATimeZeroerButton();

		void Interact() override;

private:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> TimeButtonStaticMeshComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;
	
};
