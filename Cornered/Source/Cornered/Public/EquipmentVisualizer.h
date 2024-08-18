// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquippedWeapon.h"
#include "EquipmentVisualizer.generated.h"

class UConfig_Equipment;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UEquipmentVisualizer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentVisualizer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void VisualizeEquipment(AProduct* Product);

	UFUNCTION()
		void VisualizeWeaponDatas(FItemDatas ItemDatas);

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Equipment> ConfigEquipment;

	UFUNCTION()
		void PlayEquippedWeaponVisuals();

	UFUNCTION()
		FShotRayDatas GetShotRayDatas();

private:
	UPROPERTY()
		TObjectPtr<AActor> SpawnedEquippedWeapon;

	

	UFUNCTION()
		FName GetNameOfSocket(AProduct* Product);

	UPROPERTY()
		bool bWeaponSpawned;
};
