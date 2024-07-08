// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWeapon.h"
#include "PlayerWeapon.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UPlayerWeapon : public UCharacterWeapon
{
	GENERATED_BODY()

protected:
	virtual EItemType GetEquippedWeapon() const override;

	// Called when the game starts
	virtual void BeginPlay() override;
private:

	UFUNCTION()
		void ShootHappened();
};
