// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquippedWeapon.h"
#include "Config_Equipment.h"
#include "EquipmentVisualizer.generated.h"

class AProduct;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UEquipmentVisualizer : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentVisualizer();

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		void VisualizeEquipment(AProduct* Product);

		void VisualizeWeaponDatas(FItemDatas ItemDatas);

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Equipment> ConfigEquipment;

		void PlayEquippedWeaponVisuals();

		FShotRayDatas GetShotRayDatas();

private:
	UPROPERTY()
		TObjectPtr<AActor> SpawnedEquippedWeapon;

		FName GetNameOfSocket(AProduct* Product);

		bool bWeaponSpawned;
};
