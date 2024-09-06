// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/CharacterHealth.h"
#include "Configs/DataAssets/Config_Character_General.h"
#include "Configs/DataAssets/Config_CharacterSpecific.h"
#include "System/CorneredGameMode.h"
#include "GameFramework/Character.h"

UCharacterHealth::UCharacterHealth()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = GetMaxHealth();
	bShouldReloadHealth = true;
}

float UCharacterHealth::GetMaxHealth() const {
	return SpecificCharacterConfig->MaxHealth;
}

float UCharacterHealth::GetReloadWaitingMaxTime() const {
	return SpecificCharacterConfig->WaitUntilHealthReloadStarts;
}

void UCharacterHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentHealth >= GetMaxHealth() ||
		CurrentHealth <= GeneralCharacterConfig->MinHealth)
	{
		return;
	}

	if (bShouldReloadHealth)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth += GeneralCharacterConfig->HealHealthDelta * DeltaTime, GeneralCharacterConfig->MinHealth, GetMaxHealth());
	}
}

float UCharacterHealth::GetCurrentHealth() const {
	return CurrentHealth;
}

void UCharacterHealth::DamageHealth(float Damage) {
	CurrentHealth = FMath::Clamp(CurrentHealth += Damage, GeneralCharacterConfig->MinHealth, GetMaxHealth());

	bShouldReloadHealth = false;

	if (CurrentHealth <= GeneralCharacterConfig->MinHealth)
	{
		ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
		CorneredGameMode->CharacterDied(Cast<ACharacter>(GetOwner()));
	}
	else {

		FTimerManager& TimerManager = GetWorld()->GetTimerManager();

		TimerManager.ClearTimer(TimerHandle);
		TimerManager.SetTimer(TimerHandle, this, &UCharacterHealth::HealthReloadWaitTimeEnded, GetReloadWaitingMaxTime(), false);
	}
}

void UCharacterHealth::HealthReloadWaitTimeEnded() {
	bShouldReloadHealth = true;
}