// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterWeapon.h"
#include "Config_Equipment.h"
#include "Inventory.generated.h"

class AProduct;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		void EquipItem(AProduct* Product);

		void EquipWeapon(FItemDatas itemDatas);

		void EquipShield(FItemDatas itemDatas);

		void EquipAdditional(FItemDatas itemDatas);

	UFUNCTION(BlueprintPure)
		EItemType GetWeapon() const;

private:

	EItemType Weapon;
	EItemType Shield;
	EItemType Additional;
};
