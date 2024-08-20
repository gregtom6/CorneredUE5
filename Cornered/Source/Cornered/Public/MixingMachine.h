// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorneredButton.h"
#include "Config_MixingMachine.h"
#include "MixingMachine.generated.h"

class UActorSequenceComponent;
class UActorSequencePlayer;
class UNiagaraComponent;
class AMixingItemDetector;
class UConfig_Recipe;
class UAudioComponent;

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
	
private:
	FTimerHandle TimerHandle;

		EMixingMachineState State;

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
		TObjectPtr<UActorSequenceComponent> TopLidOpenComp;

	UPROPERTY()
		TObjectPtr<UActorSequenceComponent> TopLidCloseComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UNiagaraComponent> BurningComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UNiagaraComponent> FreezingComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<AMixingItemDetector> MixingItemDetector;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_MixingMachine> MixingMachineConfig;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Recipe> RecipeConfig;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> BurnAudio;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> FreezeAudio;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> MixingAudio;
public:	
	// Sets default values for this actor's properties
	AMixingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ConvertTimeEnded();

	void BurnTimeEnded();

	void FreezeTimeEnded();

private:

	UFUNCTION()
		void OnNewMatchStarted();


	UFUNCTION()
		void ConvertPressHappened();

	UFUNCTION()
		void FreezePressHappened();

	UFUNCTION()
		void BurnPressHappened();


		float GetCurrentProcessTime(EAbility ability) const;

};
