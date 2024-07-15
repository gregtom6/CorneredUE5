// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include <CharacterWeapon.h>
#include "MixingItemDetector.generated.h"

UENUM(BlueprintType)
enum class EItemState : uint8
{
    Normal,
	Freezed,
	Burned,

    Count,
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		EItemState ItemState;

};

/**
 * 
 */
UCLASS()
class CORNERED_API AMixingItemDetector : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	AMixingItemDetector();

	UFUNCTION()
		TArray<FItemData> GetDetectedItems();

	UFUNCTION()
		void DestroyAllItems();

	UFUNCTION()
		void BurnAllItems();

	UFUNCTION()
		void FreezeAllItems();

private:

	UFUNCTION()
	void ChangeStateOfAllItems(EItemState itemState);
};
