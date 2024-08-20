// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigLevelsDevSettings.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API ULevelManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

		void LoadLevel(ELevelIdentifier LevelIdentifier, UWorld* World);
};
