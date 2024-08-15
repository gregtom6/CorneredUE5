// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ConfigLevelsDevSettings.h"

TSoftObjectPtr<UWorld> UConfigLevelsDevSettings::GetLevelBasedOnEnum(ELevelIdentifier LevelIdentifier) const {
	for (int i = 0; i < Levels.Num(); i++) {
		if (Levels[i].Key == LevelIdentifier) {
			return Levels[i].LevelToLoad;
		}
	}

	return nullptr;
}