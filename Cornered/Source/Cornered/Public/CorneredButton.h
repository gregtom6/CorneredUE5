// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "CorneredButton.generated.h"

class UAudioComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressHappenedDelegate);

UCLASS()
class CORNERED_API ACorneredButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACorneredButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact() override;

	UPROPERTY()
		FPressHappenedDelegate PressHappened;

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> PressAudio;
};
