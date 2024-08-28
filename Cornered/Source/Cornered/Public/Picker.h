// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IPickable.h"
#include "Picker.generated.h"

class UInteractableDetector;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UPicker : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY()
		TObjectPtr<UInteractableDetector> InteractableDetectorComp;

private:
	bool bPickupDropHappenedInThisFrame;

	IIPickable* PickedPickable;


public:
	// Sets default values for this component's properties
	UPicker();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	IIPickable* GetPickedPickable() const;

	void RemovePickable();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:

	UFUNCTION()
		void PickupHappened();

	UFUNCTION()
		void DropHappened();
};
