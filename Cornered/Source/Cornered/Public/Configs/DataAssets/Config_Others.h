// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Others.generated.h"

class UMaterialInterface;

UENUM()
enum class ETimerButtonState : uint8 {
	Activated,
	Deactivated,

	Count,
};


USTRUCT(BlueprintType)
struct FTimerButtonStateMaterialEntry
{
	GENERATED_BODY()

	FTimerButtonStateMaterialEntry()
		: Key(ETimerButtonState::Count) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	ETimerButtonState Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TObjectPtr<UMaterialInterface> Material;

};

UCLASS()
class CORNERED_API UConfig_Others : public UDataAsset
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = "Dictionary")
	TArray<FTimerButtonStateMaterialEntry> TimerButtonStateMaterialEntries;

public:

	UMaterialInterface* GetMaterialBasedOnState(ETimerButtonState state) const;
};
