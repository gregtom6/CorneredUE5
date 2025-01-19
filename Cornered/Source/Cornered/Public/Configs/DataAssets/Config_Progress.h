// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Configs/DataAssets/Config_MixingMachine.h"
#include "Config_Progress.generated.h"

USTRUCT(BlueprintType)
struct FUnlockableAbilities
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TArray<EAbility> Abilities;
};

USTRUCT(BlueprintType)
struct FSoulBordersPerLevels
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float SoulBorder;
};

class UCorneredGameInstance;
class AProgressionGameState;

/**
 *
 */
UCLASS()
class CORNERED_API UConfig_Progress : public UDataAsset
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	TArray<FSoulBordersPerLevels> SoulBorderCountsPerLevel;

	UPROPERTY(EditAnywhere)
	TArray<FUnlockableAbilities> AbilitiesToUnlockPerLevel;

public:

	bool IsAbilityAlreadyUnlocked(EAbility ability, UCorneredGameInstance* gameInstance);

	int GetMaxUnlockLevel() const;

	bool IsAbilityUnlocked(EAbility Ability, AProgressionGameState* GameState);

	int32 GetSoulBorderCount(UWorld* World);

private:

	TArray<EAbility> GetAlreadyUnlockedAbilities(int currentUnlockLevel) const;
};
