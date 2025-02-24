// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Environment/Interactables/Holdable.h"
#include "Interactor.generated.h"

class UInteractableDetector;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UInteractor : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UInteractableDetector> InteractableDetectorComp;

	bool bInteractHappenedInThisFrame;
	IHoldable* Holdable;

public:
	// Sets default values for this component's properties
	UInteractor();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void InteractStarted();

	UFUNCTION()
	void InteractHappened();
};
