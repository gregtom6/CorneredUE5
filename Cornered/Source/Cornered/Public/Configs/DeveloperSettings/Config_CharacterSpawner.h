// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Config_CharacterSpawner.generated.h"

class UConfig_Character_General;
class AActor;
class ASoul;

/**
 *
 */
UCLASS(config = Game, defaultconfig)
class CORNERED_API UConfig_CharacterSpawner : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(config, EditAnywhere)
	TArray<TSoftObjectPtr<UWorld>> ActiveInTheseLevels;

	UPROPERTY(config, EditAnywhere)
	TSoftObjectPtr<UConfig_Character_General> CharacterConfig;

	UPROPERTY(config, EditAnywhere)
	TSubclassOf<ASoul> SoulClass;
};
