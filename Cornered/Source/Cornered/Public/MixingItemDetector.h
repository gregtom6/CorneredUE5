// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ItemType.h"
#include "ItemState.h"
#include "MixingItemDetector.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

		FItemData()
		: ItemType(EItemType::Count), ItemState(EItemState::Count) { }

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
		EItemState ItemState;

};

UCLASS()
class CORNERED_API AMixingItemDetector : public ATriggerBox
{
	GENERATED_BODY()
	
public:

		TArray<FItemData> GetDetectedItems();

		void DestroyAllItems();

		void BurnAllItems();

		void FreezeAllItems();

private:

	void ChangeStateOfAllItems(EItemState itemState);
};
