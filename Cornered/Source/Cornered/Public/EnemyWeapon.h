// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWeapon.h"
#include "EnemyWeapon.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UEnemyWeapon : public UCharacterWeapon
{
	GENERATED_BODY()
	
protected:
	virtual EItemType GetEquippedWeapon() const override;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};