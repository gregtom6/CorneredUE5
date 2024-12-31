// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "Environment/Others/LightBlinkable.h"
#include "EquipmentHint.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UConfig_Hint;
class URectLightComponent;
class ULightBlinkController;

UENUM()
enum class EEquipment :uint8
{
	Weapon,
	Shield,
	Additional,

	Count,
};

UCLASS()
class CORNERED_API AEquipmentHint : public AActor, public ILightBlinkable
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ShieldMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WeaponMeshComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Hint> HintConfig;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> RectLightWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> RectLightShield;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> LightMeshWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> LightMeshShield;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ULightBlinkController> LightBlinkController;

public:
	AEquipmentHint();

protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnEquipmentDecided(FItemDatas Weapon, FItemDatas Shield, FItemDatas Additional);

	// Inherited via ILightBlinkable
	TArray<ULightComponent*> GetLightComponents() override;

	// Inherited via ILightBlinkable
	TArray<UMaterialInstanceDynamic*> GetLightMaterials() override;
};
