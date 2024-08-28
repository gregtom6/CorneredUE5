// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemType.h"
#include "EquippedWeapon.h"
#include "Config_Equipment.h"
#include "CharacterWeapon.generated.h"

UCLASS(Abstract, ClassGroup = (Custom))
class CORNERED_API UCharacterWeapon : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Equipment> EquipmentConfig;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = IsReadyToShoot)
		bool bIsReadyToShoot = true;

private:

	FTimerHandle TimerHandle;

public:
	UCharacterWeapon();

	float GetCooldownTimeLeftPercentageBetween01();

	UFUNCTION(BlueprintPure)
		bool IsThereEquippedWeapon() const;


	void SetWeaponReadyToBeUsed();

	UFUNCTION(BlueprintGetter)
		bool IsReadyToShoot() const;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
		EItemType GetEquippedWeapon() const;

	void ShootWithEquippedWeapon();

	void ManageVisual();


	UFUNCTION()
		void ShootCooldownEnded();

	void InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) const;

private:

	void DamageTheOtherOneIfCan(FWeaponSettingsEntry weaponSettings);

	virtual ECollisionChannel GetOpponentTraceChannel() const PURE_VIRTUAL(UCharacterWeapon::GetOpponentTraceChannel, return ECollisionChannel::ECC_Visibility;);
};
