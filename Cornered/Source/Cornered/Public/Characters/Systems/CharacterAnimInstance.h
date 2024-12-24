// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class CORNERED_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LegState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UseWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsRepairing;
};
