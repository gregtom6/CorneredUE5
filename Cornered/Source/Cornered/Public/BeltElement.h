// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeltElement.generated.h"

class ABeltController;
class UConfig_IngredientGeneration;

UCLASS()
class CORNERED_API ABeltElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeltElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetBeltController(ABeltController* controller);

	virtual void SetActorHiddenInGame(bool bNewHidden) override;

private:

	UPROPERTY()
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> ItemPivot;

	UPROPERTY()
		TObjectPtr<ABeltController> BeltController;

	UPROPERTY(EditAnywhere)
		UConfig_IngredientGeneration* IngredientGenConfig;

	FTimerHandle TimerHandle;

	FVector ItemPivotLocation;

	void TimerFunction();
};
