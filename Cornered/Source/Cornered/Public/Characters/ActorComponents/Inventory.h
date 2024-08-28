// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/ActorComponents/CharacterWeapon.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "Inventory.generated.h"

class AProduct;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UInventory : public UActorComponent
{
	GENERATED_BODY()

private:

	EItemType Weapon;
	EItemType Shield;
	EItemType Additional;
public:
	// Sets default values for this component's properties
	UInventory();
	void EquipItem(AProduct* Product);

	void EquipWeapon(FItemDatas itemDatas);

	void EquipShield(FItemDatas itemDatas);

	void EquipAdditional(FItemDatas itemDatas);

	UFUNCTION(BlueprintPure)
		EItemType GetWeapon() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
