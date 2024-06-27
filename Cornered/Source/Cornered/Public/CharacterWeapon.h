// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterWeapon.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    EmptyItem,
    Tube,
    Marbles,
    Board,
    Coffee,
    Boots,
    Petrol,
    Pistol,
    Shotgun,
    FastBoots,
    FlamingShotgun,
    Freezer,
    DefenderPhysical,
    DefenderPhysicalExtra,
    DefenderHeat,
    DefenderCold,
    Rope,

    Count,
};

UCLASS(Abstract, ClassGroup = (Custom))
class CORNERED_API UCharacterWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UFUNCTION()
        virtual EItemType GetEquippedWeapon() const PURE_VIRTUAL(UCharacterWeapon::GetEquippedWeapon, return EItemType::Count;);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		bool IsThereEquippedWeapon() const;
};
