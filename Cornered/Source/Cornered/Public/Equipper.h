// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Equipper.generated.h"

class UPicker;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UEquipper : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipper();

	UPROPERTY()
		TObjectPtr<UPicker> PickerComp;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
		void EquipHappened();
};
