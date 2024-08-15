// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CharacterWeapon.h"
#include "Config_Equipment.h"
#include <EquipmentVisualizer.h>
#include <Kismet/GameplayStatics.h>
#include "EquippedWeapon.h"

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

	DamageTheOtherOneIfCan(weaponSettings);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCharacterWeapon::ShootCooldownEnded, weaponSettings.CooldownTimeInSec, false);
}

void UCharacterWeapon::DamageTheOtherOneIfCan(FWeaponSettingsEntry weaponSettings) {

	UEquipmentVisualizer* equipmentVisualizer = Cast<UEquipmentVisualizer>(GetOwner()->GetComponentByClass(UEquipmentVisualizer::StaticClass()));

	FShotRayDatas shotRayDatas = equipmentVisualizer->GetShotRayDatas();

	InflictDamage(weaponSettings, shotRayDatas);
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

void UCharacterWeapon::InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) {

}

bool UCharacterWeapon::IsReadyToShoot() {
	return bIsReadyToShoot;
}