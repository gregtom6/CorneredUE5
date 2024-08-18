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
	UCharacterWeapon();

protected:
	virtual void BeginPlay() override;

    UFUNCTION()
        virtual EItemType GetEquippedWeapon() const PURE_VIRTUAL(UCharacterWeapon::GetEquippedWeapon, return EItemType::Count;);

    UFUNCTION()
        void ShootWithEquippedWeapon();

    UFUNCTION()
        void ManageVisual();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = IsReadyToShoot)
        bool bIsReadyToShoot = true;

    void ShootCooldownEnded();

    UFUNCTION()
        virtual void InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) const PURE_VIRTUAL(UCharacterWeapon::InflictDamage, );

public:	
    UFUNCTION()
        float GetCooldownTimeLeftPercentageBetween01();

	UFUNCTION()
		bool IsThereEquippedWeapon() const;

    UPROPERTY(EditAnywhere)
        TObjectPtr<UConfig_Equipment> EquipmentConfig;

    UFUNCTION()
        void SetWeaponReadyToBeUsed();

    UFUNCTION(BlueprintGetter)
        bool IsReadyToShoot();

private:
    FTimerHandle TimerHandle;

    UFUNCTION()
        void DamageTheOtherOneIfCan(FWeaponSettingsEntry weaponSettings);

};
