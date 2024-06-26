// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Character_General.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Character_General : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyRunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HeadMinRotY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HeadMaxRotY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyMaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WaitUntilHealthReloadStarts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HealHealthDelta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FastBootsSpeedMultiplier;
};
