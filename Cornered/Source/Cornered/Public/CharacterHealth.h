// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterHealth.generated.h"

class UConfig_Character_General;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UCharacterHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterHealth();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetCurrentHealth)
		float CurrentHealth;

	UPROPERTY(BlueprintReadWrite)
		float MaxHealth;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Character_General> CharacterConfig;

	void HealthReloadWaitTimeEnded();

	virtual float GetReloadWaitingMaxTime();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
		float GetCurrentHealth();

		virtual float GetMaxHealth();

		UFUNCTION()
			void DamageHealth(float Damage);

private:

	FTimerHandle TimerHandle;

	UPROPERTY()
		bool bShouldReloadHealth;

};
