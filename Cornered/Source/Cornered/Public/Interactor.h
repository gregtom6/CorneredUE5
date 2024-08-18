// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Holdable.h"
#include "Interactor.generated.h"

class UInteractableDetector;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UInteractor : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractor();

	UPROPERTY()
		TObjectPtr<UInteractableDetector> InteractableDetectorComp;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

		bool bInteractHappenedInThisFrame;

	UFUNCTION()
		void InteractStarted();

	UFUNCTION()
		void InteractHappened();

private:
	
		IHoldable* Holdable;

};
