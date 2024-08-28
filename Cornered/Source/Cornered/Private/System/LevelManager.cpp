// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/LevelManager.h"
#include <Kismet/GameplayStatics.h>

void ULevelManager::LoadLevel(ELevelIdentifier LevelIdentifier, UWorld* World) {

	const UConfigLevelsDevSettings* Settings = GetDefault<UConfigLevelsDevSettings>();

	if (Settings) {

		TSoftObjectPtr<UWorld> LevelToLoad = Settings->GetLevelBasedOnEnum(LevelIdentifier);
		if (!LevelToLoad.IsNull()){

			UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoad);
		}
	}
}