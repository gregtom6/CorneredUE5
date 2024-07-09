// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWeapon.h"
#include "Config_Equipment.h"
#include <EquipmentVisualizer.h>

// Sets default values for this component's properties
UCharacterWeapon::UCharacterWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterWeapon::BeginPlay()
{
	Super::BeginPlay();

	bIsReadyToShoot = false;
	
}


// Called every frame
void UCharacterWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UCharacterWeapon::IsThereEquippedWeapon() const {
	return GetEquippedWeapon() != EItemType::Count;
}

void UCharacterWeapon::ShootWithEquippedWeapon() {
	if (!IsThereEquippedWeapon() || !bIsReadyToShoot) {
		return;
	}

	ManageVisual();

	bIsReadyToShoot = false;

	FWeaponSettingsEntry weaponSettings = EquipmentConfig->GetWeaponSettings(GetEquippedWeapon());

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCharacterWeapon::ShootCooldownEnded, weaponSettings.CooldownTimeInSec, false);
}

void UCharacterWeapon::ShootCooldownEnded() {
	bIsReadyToShoot = true;
}

void UCharacterWeapon::ManageVisual() {
	UEquipmentVisualizer* equipmentVisualizer = Cast<UEquipmentVisualizer>(GetOwner()->GetComponentByClass(UEquipmentVisualizer::StaticClass()));

	if (equipmentVisualizer) {
		equipmentVisualizer->PlayEquippedWeaponVisuals();
	}
}

void UCharacterWeapon::SetWeaponReadyToBeUsed() {
	bIsReadyToShoot = true;
}

float UCharacterWeapon::GetCooldownTimeLeftPercentageBetween01() {
	

	bool bIsTimerActive = GetWorld()->GetTimerManager().IsTimerActive(TimerHandle);

	if (bIsTimerActive) {

		FWeaponSettingsEntry weaponSettings = EquipmentConfig->GetWeaponSettings(GetEquippedWeapon());

		float ElapsedTime = GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle);

		return FMath::Clamp(ElapsedTime / weaponSettings.CooldownTimeInSec, 0.f, 1.f);
	}
	
	return 1.0f;
	
}