// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractableDetector.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UInteractableDetector : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableDetector();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		bool ItWasValidHit();

	UFUNCTION()
		FHitResult GetHitResult();

private:

	UPROPERTY()
		TObjectPtr<UWorld> CachedWorld;

	UPROPERTY()
		bool bIsValidHit;

	UPROPERTY()
		FHitResult HitResult;
};
