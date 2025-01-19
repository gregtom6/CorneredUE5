// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Materials/MaterialInterface.h"
#include "Config_SoulSniffer.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_SoulSniffer : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	float TimeBeforeCatchSoul;

	UPROPERTY(EditAnywhere)
	float TimeBetweenCatchAndProcess;

	UPROPERTY(EditAnywhere)
	float TimeForProcess;

	UPROPERTY(EditAnywhere)
	float TimeAfterProcess;

	UPROPERTY(EditAnywhere)
	float TimeForTextBrightness;

	UPROPERTY(EditAnywhere)
	int32 DigitNumber;

	UPROPERTY(EditAnywhere)
	float TimeUntilAlarm;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> DisabledGreyLight;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> ActiveWhiteLight;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> DisabledGreyText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> ActiveWhiteText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> ActiveGreenText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> ActiveRedText;
};
