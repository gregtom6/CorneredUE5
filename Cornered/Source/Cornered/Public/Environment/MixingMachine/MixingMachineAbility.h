// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Configs/DataAssets/Config_MixingMachine.h"
#include "Items/ItemState.h"
#include "MixingMachineAbility.generated.h"

class ACorneredButton;
class UConfig_MixingMachine;
class UNiagaraSystem;
class UConfig_Recipe;
class AMixingItemDetector;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityActivatedDelegate, UMixingMachineAbility*, ActivatedAbility);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UMixingMachineAbility : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UNiagaraSystem> AbilityNiagara;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> AbilitySound;

	FAbilityActivatedDelegate AbilityActivated;

private:

	UPROPERTY(EditAnywhere)
	bool bShouldAddEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ACorneredButton> AbilityButton;
	UPROPERTY(EditAnywhere)
	bool bShouldCreateResult;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_MixingMachine> MixingMachineConfig;

	UPROPERTY(EditAnywhere)
	EAbility AbilityType;

	UPROPERTY(EditAnywhere)
	EItemState ItemStateAfterAbility;

public:	
	// Sets default values for this component's properties
	UMixingMachineAbility();

	void AbilityTimeEnded(AMixingItemDetector* MixingItemDetector, UConfig_Recipe* RecipeConfig, FVector ResultLocation);

	void SetButtonStatus();
	float GetCurrentProcessTime() const;

protected:
	virtual void BeginPlay() override;

private:

	void ResultCreation(AMixingItemDetector* MixingItemDetector, UConfig_Recipe* RecipeConfig, FVector ResultLocation);

	void AddingEffectOnItems(AMixingItemDetector* MixingItemDetector);

	UFUNCTION()
	void AbilityPressHappened();
};
