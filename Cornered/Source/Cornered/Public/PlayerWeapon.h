// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWeapon.h"
#include "PlayerWeapon.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UPlayerWeapon : public UCharacterWeapon
{
	GENERATED_BODY()

protected:
	virtual EItemType GetEquippedWeapon() const override;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) const override;
private:

	UFUNCTION()
		void ShootHappened();

};
