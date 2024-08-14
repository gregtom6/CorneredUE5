// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CharacterHealth.h"
#include "Config_Character_General.h"

// Sets default values for this component's properties
UCharacterHealth::UCharacterHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = GetMaxHealth();
	bShouldReloadHealth = true;
}


// Called every frame
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
		UE_LOG(LogTemp, Log, TEXT("Enemy defeated"));
		//EventManager.Raise(new CharacterDefeatedEvent{ characterType = GetCharacterType() });
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