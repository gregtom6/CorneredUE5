// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "ConfigEquipmentDevSettings.generated.h"

/**
 *
 */
UCLASS(config = Game, defaultconfig)
class CORNERED_API UConfigEquipmentDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(config, EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> ActiveInTheseLevels;

private:

	UPROPERTY(config, EditAnywhere)
	TArray<FItemDatas> Weapons;
	UPROPERTY(config, EditAnywhere)
	TArray<FItemDatas> Shields;
	UPROPERTY(config, EditAnywhere)
	TArray<FItemDatas> Additionals;

public:

	FItemDatas GetRandomWeapon() const;

	FItemDatas GetRandomShield() const;

	FItemDatas GetRandomAdditional() const;

};
