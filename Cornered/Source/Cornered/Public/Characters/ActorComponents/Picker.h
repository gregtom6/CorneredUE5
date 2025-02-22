// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Items/IPickable.h"
#include "Picker.generated.h"

class UInteractableDetector;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UPicker : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UInteractableDetector> InteractableDetectorComp;

	bool bPickupDropHappenedInThisFrame;

	IIPickable* PickedPickable;

public:
	// Sets default values for this component's properties
	UPicker();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	IIPickable* GetPickedPickable() const;

	FVector GetPickedPickablePosition();

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
