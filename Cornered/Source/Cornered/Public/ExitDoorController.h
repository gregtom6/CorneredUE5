// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HoldActivable.h"
#include "ExitDoorController.generated.h"

class UTextRenderComponent;
class UStaticMeshComponent;
class UActorSequenceComponent;
class UActorSequencePlayer;
class UConfig_ExitDoor;
class AHoldableButton;
class AExitButtonMover;
/**
 * 
 */
UCLASS()
class CORNERED_API AExitDoorController : public AHoldActivable
{
	GENERATED_BODY()

public:

	AExitDoorController();

	virtual void Tick(float DeltaTime) override;

	virtual void HoldProcessStarted() override;

	virtual void HoldProcessEnded() override;

protected:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> DoorVisuals;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UTextRenderComponent> PercentageText;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UTextRenderComponent> ProgressText;

	UPROPERTY(EditAnywhere)
		UConfig_ExitDoor* ExitDoorConfig;

	UPROPERTY()
		UActorSequenceComponent* OpenSequ;

	UPROPERTY(EditAnywhere)
		TObjectPtr<AHoldableButton> HoldableButton;

	UPROPERTY(EditAnywhere)
		TObjectPtr<AExitButtonMover> ExitButtonParent;

	UPROPERTY()
		bool bOpeningInProgress;

	UPROPERTY()
		float OpeningPercentage;

	UFUNCTION()
		void PrintPercentageText();

	UPROPERTY()
		bool bDoorOpened;
};
