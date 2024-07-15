// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterWeapon.h"
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

	UFUNCTION()
		void EquipItem(AProduct* Product);

	UFUNCTION()
		EItemType GetWeapon() const;

private:

	UPROPERTY()
	EItemType Weapon;
	UPROPERTY()
	EItemType Shield;
	UPROPERTY()
	EItemType Additional;
};
