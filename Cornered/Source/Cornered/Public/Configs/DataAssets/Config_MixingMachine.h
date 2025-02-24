// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_MixingMachine.generated.h"

UENUM(BlueprintType)
enum class EAbility : uint8
{
	Default,
	Burn,
	Freeze,

	Count,
};

USTRUCT(BlueprintType)
struct FAbilityProcessTimeEntry
{
	GENERATED_BODY()

	FAbilityProcessTimeEntry()
		: Key(EAbility::Count), ProcessTime(0.f) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EAbility Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float ProcessTime;
};

UCLASS()
class CORNERED_API UConfig_MixingMachine : public UDataAsset
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Dictionary")
	TArray<FAbilityProcessTimeEntry> AbilityProcessTimeEntries;

public:

	float GetProcessTime(EAbility ability) const;

};
