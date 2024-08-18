// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CharacterHealth.h"
#include "Config_Character_General.h"
#include "CorneredGameMode.h"
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

void UCharacterHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentHealth >= GetMaxHealth() ||
		CurrentHealth <= CharacterConfig->MinHealth)
	{
		return;
	}

	if (bShouldReloadHealth)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth += CharacterConfig->HealHealthDelta * DeltaTime, CharacterConfig->MinHealth, GetMaxHealth());
	}
}

float UCharacterHealth::GetCurrentHealth() {
	return CurrentHealth;
}

float UCharacterHealth::GetMaxHealth() {
	return MaxHealth;
}

void UCharacterHealth::DamageHealth(float Damage) {
	CurrentHealth = FMath::Clamp(CurrentHealth += Damage, CharacterConfig->MinHealth, GetMaxHealth());

	bShouldReloadHealth = false;

	if (CurrentHealth <= CharacterConfig->MinHealth)
	{
		ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
		CorneredGameMode->CharacterDied(Cast<ACharacter>(GetOwner()));
	}
	else {


		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCharacterHealth::HealthReloadWaitTimeEnded, GetReloadWaitingMaxTime(), false);
	}
}

void UCharacterHealth::HealthReloadWaitTimeEnded() {
	bShouldReloadHealth = true;
}

float UCharacterHealth::GetReloadWaitingMaxTime() {
	return 0.f;
}