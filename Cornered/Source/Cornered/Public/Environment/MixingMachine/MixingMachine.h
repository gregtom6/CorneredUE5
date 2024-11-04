// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MixingMachine.generated.h"

class UActorSequenceComponent;
class UActorSequencePlayer;
class UNiagaraComponent;
class AMixingItemDetector;
class UConfig_Recipe;
class UAudioComponent;
class UMixingMachineAbility;
class ACorneredButton;

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

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> TopLidOpenComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> TopLidCloseComp;

private:
	FTimerHandle TimerHandle;

	EMixingMachineState State;

	UPROPERTY()
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> ResultTarget;

	TArray<TObjectPtr<UMixingMachineAbility>> AbilityComponents;

	TObjectPtr<UMixingMachineAbility> CurrentlyUsedAbility;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> AbilityComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> CreationNiagaraComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> CreationAudio;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AMixingItemDetector> MixingItemDetector;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Recipe> RecipeConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> AbilityAudio;
public:
	// Sets default values for this actor's properties
	AMixingMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnNewMatchStarted();

	void AbilityTimeEnded();

	void CreateResult();

	UFUNCTION()
	void AbilityPressHappened(UMixingMachineAbility* SelectedAbility);
};
