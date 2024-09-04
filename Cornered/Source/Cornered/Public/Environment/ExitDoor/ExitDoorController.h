// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Environment/Interactables/HoldActivable.h"
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

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> OpenSequ;

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
	TObjectPtr<UConfig_ExitDoor> ExitDoorConfig;


	UPROPERTY(EditAnywhere)
	TObjectPtr<AHoldableButton> HoldableButton;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AExitButtonMover> ExitButtonParent;

	bool bOpeningInProgress;

	float OpeningPercentage;

	bool bDoorOpened;

public:

	AExitDoorController();

	virtual void Tick(float DeltaTime) override;

	virtual void HoldProcessStarted() override;

	virtual void HoldProcessEnded() override;

protected:

	virtual void BeginPlay() override;

private:

	void PrintPercentageText();

};
