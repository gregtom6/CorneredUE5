// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorneredButton.h"
#include "MixingMachine.generated.h"

class UActorSequenceComponent;
class UActorSequencePlayer;
class UNiagaraComponent;
class AMixingItemDetector;
class UConfig_MixingMachine;
class UConfig_Recipe;


UENUM(BlueprintType)
enum class EMixingMachineState :uint8
{
	DoingProcess,
	Waiting,

	Count,
};

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

	void ConvertTimeEnded();

	void BurnTimeEnded();

	void FreezeTimeEnded();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	FTimerHandle TimerHandle;

	UFUNCTION()
		void ConvertPressHappened();

	UFUNCTION()
		void FreezePressHappened();

	UFUNCTION()
		void BurnPressHappened();

	UPROPERTY()
		EMixingMachineState State;

	UFUNCTION()
		float GetCurrentProcessTime(EAbility ability);

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
		UActorSequenceComponent* TopLidOpenComp;

	UPROPERTY()
		UActorSequenceComponent* TopLidCloseComp;

	UPROPERTY(VisibleAnywhere)
		UNiagaraComponent* BurningComp;

	UPROPERTY(VisibleAnywhere)
		UNiagaraComponent* FreezingComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<AMixingItemDetector> MixingItemDetector;

	UPROPERTY(EditAnywhere)
		UConfig_MixingMachine* MixingMachineConfig;

	UPROPERTY(EditAnywhere)
		UConfig_Recipe* RecipeConfig;
};
