// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ConfigLevelsDevSettings.generated.h"

UENUM()
enum class ELevelIdentifier : uint8 {
	MainMenu,
	MainScene,
	GameOverScene,
	GameWinScene,

	Count,
};

USTRUCT(BlueprintType)
struct FLevelEntry
{
	GENERATED_BODY()

		FLevelEntry()
		: Key(ELevelIdentifier::Count) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		ELevelIdentifier Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		TSoftObjectPtr<UWorld> LevelToLoad;

};

UCLASS(config = Game, defaultconfig)
class CORNERED_API UConfigLevelsDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(config, EditAnywhere)
		TArray<FLevelEntry> Levels;

public:

	UFUNCTION()
		TSoftObjectPtr<UWorld> GetLevelBasedOnEnum(ELevelIdentifier LevelIdentifier) const;
};
