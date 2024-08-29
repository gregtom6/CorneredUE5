// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/EquippedWeapon.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "EquipmentVisualizer.generated.h"

class AProduct;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UEquipmentVisualizer : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Equipment> ConfigEquipment;

private:

	UPROPERTY()
		TObjectPtr<AActor> SpawnedEquippedWeapon;

	bool bWeaponSpawned;

public:
	UEquipmentVisualizer();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void VisualizeEquipment(AProduct* Product);

	void VisualizeWeaponDatas(FItemDatas ItemDatas);


	void PlayEquippedWeaponVisuals();

	FShotRayDatas GetShotRayDatas() const;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	FName GetNameOfSocket(AProduct* Product) const;

	FName GetNameOfSocketBasedOnItemType(EItemType ItemType) const;

	void ActualVisualization(EItemType ItemType, FName SocketName);
};
