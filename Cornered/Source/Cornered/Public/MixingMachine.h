// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorneredButton.h"
#include "MixingMachine.generated.h"

class UActorSequenceComponent;
class UActorSequencePlayer;
class UNiagaraComponent;

UCLASS()
class CORNERED_API AMixingMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMixingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> ResultTarget;

	UPROPERTY(EditAnywhere)
		TObjectPtr<ACorneredButton> ConvertButton;

	UPROPERTY(EditAnywhere)
		TObjectPtr<ACorneredButton> BurnButton;

	UPROPERTY(EditAnywhere)
		TObjectPtr<ACorneredButton> FreezeButton;

	UPROPERTY()
		UActorSequenceComponent* TopLidOpen;

	UPROPERTY()
		UActorSequenceComponent* TopLidClose;

	UPROPERTY(VisibleAnywhere)
		UNiagaraComponent* BurningComp;

	UPROPERTY(VisibleAnywhere)
		UNiagaraComponent* FreezingComp;
};
