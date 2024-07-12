// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Holdable.h"
#include "HoldableButton.generated.h"

class AHoldActivable;

UCLASS()
class CORNERED_API AHoldableButton : public AActor, public IHoldable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHoldableButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HoldingStarted() override;

	virtual void HoldingFinished() override;

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<AHoldActivable> HoldActivable;

};
