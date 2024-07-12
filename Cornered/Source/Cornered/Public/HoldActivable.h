// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoldActivable.generated.h"

UCLASS(Abstract)
class CORNERED_API AHoldActivable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHoldActivable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void HoldProcessStarted() PURE_VIRTUAL(AHoldActivable::HoldProcessStarted, );

	UFUNCTION()
		virtual void HoldProcessEnded() PURE_VIRTUAL(AHoldActivable::HoldProcessEnded, );
};
