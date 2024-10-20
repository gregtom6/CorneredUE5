// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/CharacterWeapon.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include <Kismet/GameplayStatics.h>
#include "Items/EquippedWeapon.h"
#include "GameFramework/Pawn.h"
#include "Characters/ActorComponents/Inventory.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Engine/DamageEvents.h"

UCharacterWeapon::UCharacterWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterWeapon::BeginPlay()
{
	Super::BeginPlay();

	bIsReadyToShoot = false;

	TimerManager = &GetWorld()->GetTimerManager();

	HealthComp = GetOwner()->FindComponentByClass<UCharacterHealth>();
}

bool UCharacterWeapon::IsThereEquippedWeapon() const {
	return GetEquippedWeapon() != EItemType::Count;
}

EItemType UCharacterWeapon::GetEquippedWeapon() const {

	UInventory* inventory = GetOwner()->FindComponentByClass<UInventory>();
	return inventory->GetWeapon();
}

void UCharacterWeapon::ShootWithEquippedWeapon() {
	if (!IsThereEquippedWeapon() || !bIsReadyToShoot) {
		return;
	}

	ManageVisual();

	bIsReadyToShoot = false;

	FWeaponSettingsEntry weaponSettings = EquipmentConfig->GetWeaponSettings(GetEquippedWeapon());

	DamageTheOtherOneIfCan(weaponSettings);

	TimerManager->ClearTimer(TimerHandle);
	TimerManager->SetTimer(TimerHandle, this, &UCharacterWeapon::ShootCooldownEnded, weaponSettings.CooldownTimeInSec, false);
}

void UCharacterWeapon::DamageTheOtherOneIfCan(FWeaponSettingsEntry weaponSettings) {
	FShotRayDatas shotRayDatas = GetShotRayDatas();

	InflictDamage(weaponSettings, shotRayDatas);
}

FShotRayDatas UCharacterWeapon::GetShotRayDatas() const {
	UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();

	return equipmentVisualizer->GetShotRayDatas();
}

void UCharacterWeapon::ShootCooldownEnded() {
	bIsReadyToShoot = true;
}

void UCharacterWeapon::ManageVisual() {
	UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();

	if (equipmentVisualizer) {
		equipmentVisualizer->PlayEquippedWeaponVisuals();
	}
}

void UCharacterWeapon::SetWeaponReadyToBeUsed() {
	bIsReadyToShoot = true;
}

float UCharacterWeapon::GetCooldownTimeLeftPercentageBetween01() const {
	
	bool bIsTimerActive = TimerManager->IsTimerActive(TimerHandle);

	if (bIsTimerActive) {

		FWeaponSettingsEntry weaponSettings = EquipmentConfig->GetWeaponSettings(GetEquippedWeapon());

		float ElapsedTime = TimerManager->GetTimerElapsed(TimerHandle);

		return FMath::Clamp(ElapsedTime / weaponSettings.CooldownTimeInSec, 0.f, 1.f);
	}
	
	return 1.0f;
	
}

bool UCharacterWeapon::IsReadyToShoot() const {
	return bIsReadyToShoot;
}

void UCharacterWeapon::InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) const {
	FVector Origin = shotRayDatas.Origin;

	FVector End = shotRayDatas.End;

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Origin,
		End,
		GetOpponentTraceChannel()
	);

	if (bHit) {

		APawn* Pawn = Cast<APawn>(HitResult.GetActor());
		if (Pawn) {

			FPointDamageEvent DamageEvent;
			DamageEvent.Damage = weaponSettings.Damage; 

			Pawn->TakeDamage(weaponSettings.Damage,DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
		}
	}
}