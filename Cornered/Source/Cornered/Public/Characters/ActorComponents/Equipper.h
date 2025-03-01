// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Equipper.generated.h"

class UPicker;
class UCameraComponent;
class UConfig_Equipment;

UENUM(BlueprintType)
enum class EPickedFlyState :uint8
{
	NotFlying,
	Flying,

	Count,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UEquipper : public USceneComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UPicker> PickerComp;

	EPickedFlyState State;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Equipment> EquipmentConfig;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void EquipHappened();

	UFUNCTION()
	void ActualEquip();
};
