// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class CORNERED_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int LegState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseWeapon;

	UFUNCTION(BlueprintCallable)
		void OnStateAnimationEnds();
};
