// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Config_Equipment.h"
#include "EquipmentDecider.generated.h"

class UCharacterSpawner;
class UConfig_Equipment;
class AEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEquipmentDecidedDelegate, FItemDatas, Weapon, FItemDatas, Shield, FItemDatas, Additional);

UCLASS()
class CORNERED_API UEquipmentDecider : public UWorldSubsystem
{
	GENERATED_BODY()
	
protected:
	UFUNCTION()
		void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

	UFUNCTION()
		void GenerateEquipment(AEnemyCharacter* EnemyCharacter);

public:

	UPROPERTY()
		FEquipmentDecidedDelegate OnEquipmentDecided;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
