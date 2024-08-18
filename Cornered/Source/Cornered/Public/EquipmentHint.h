// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Config_Equipment.h"
#include "EquipmentHint.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UConfig_Hint;

UENUM()
enum class EEquipment :uint8
{
	Weapon,
	Shield,
	Additional,

	Count,
};

UCLASS()
class CORNERED_API AEquipmentHint : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipmentHint();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> ShieldMeshComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> WeaponMeshComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Hint> HintConfig;

	UFUNCTION()
		void OnEquipmentDecided(FItemDatas Weapon, FItemDatas Shield, FItemDatas Additional);
};
