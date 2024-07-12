// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExitButtonMover.generated.h"

class UActorSequenceComponent;
class UActorSequencePlayer;

UCLASS()
class CORNERED_API AExitButtonMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitButtonMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void StartMoving();

private:

	UPROPERTY()
		UActorSequenceComponent* OpenSequ;

	UPROPERTY(EditAnywhere)
		USceneComponent* Root;
};