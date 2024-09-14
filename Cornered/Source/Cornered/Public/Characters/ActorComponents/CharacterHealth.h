// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "System/CorneredGameMode.h"
#include "CharacterHealth.generated.h"

class UConfig_Character_General;
class UConfig_CharacterSpecific;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UCharacterHealth : public UActorComponent
{
	GENERATED_BODY()

public:

	FCharacterDefeatedDelegate CharacterDefeated;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetCurrentHealth)
	float CurrentHealth;

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Character_General> GeneralCharacterConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_CharacterSpecific> SpecificCharacterConfig;

private:

	FTimerHandle TimerHandle;

	bool bShouldReloadHealth;

public:
	UCharacterHealth();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
	float GetCurrentHealth() const;

	float GetMaxHealth() const;

	void DamageHealth(float Damage);

protected:
	virtual void BeginPlay() override;


	void HealthReloadWaitTimeEnded();

private:
	float GetReloadWaitingMaxTime() const;
};
