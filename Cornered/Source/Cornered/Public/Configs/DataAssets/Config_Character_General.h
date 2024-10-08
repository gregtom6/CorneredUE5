// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Character_General.generated.h"

class AEnemyCharacter;

/**
 *
 */
UCLASS()
class CORNERED_API UConfig_Character_General : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeadMinRotY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeadMaxRotY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealHealthDelta;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FastBootsSpeedMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LookVerticalSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LookHorizontalSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WhenReceivingShotHeadXRotationMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WhenReceivingShotHeadXRotationMax;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyCharacter> EnemyCharacterClass;
};
