// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterHealth.generated.h"

class UConfig_Character_General;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UCharacterHealth : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetCurrentHealth)
		float CurrentHealth;

	UPROPERTY(BlueprintReadWrite)
		float MaxHealth;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Character_General> CharacterConfig;

private:

	FTimerHandle TimerHandle;

	bool bShouldReloadHealth;

public:
	UCharacterHealth();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
		float GetCurrentHealth();

	virtual float GetMaxHealth();

	void DamageHealth(float Damage);

protected:
	virtual void BeginPlay() override;


	void HealthReloadWaitTimeEnded();

	virtual float GetReloadWaitingMaxTime();
};
