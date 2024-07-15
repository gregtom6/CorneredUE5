// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void VisualizeEquipment(AProduct* Product);

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Equipment> ConfigEquipment;

	UFUNCTION()
		void PlayEquippedWeaponVisuals();


private:
	UPROPERTY()
		TObjectPtr<AActor> SpawnedEquippedWeapon;

	UFUNCTION()
		FName GetNameOfSocket(AProduct* Product);

	UPROPERTY()
		bool bWeaponSpawned;
};
