// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include <CharacterWeapon.h>
#include "MixingItemDetector.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
    Normal,
	Freezed,
	Burned,

    Count,
};

/**
 * 
 */
UCLASS()
class CORNERED_API AMixingItemDetector : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	AMixingItemDetector();

	UFUNCTION()
		TArray<EItemType> GetDetectedItems();

	UFUNCTION()
		void DestroyAllItems();

	UFUNCTION()
		void BurnAllItems();

	UFUNCTION()
		void FreezeAllItems();

private:

	UFUNCTION()
	void ChangeStateOfAllItems(EItemState itemState);
};
