// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Items/ItemData.h"
#include "MixingItemDetector.generated.h"

UCLASS()
class CORNERED_API AMixingItemDetector : public ATriggerBox
{
	GENERATED_BODY()

public:

	TArray<FItemData> GetDetectedItems() const;

	bool AreThereDetectedItems();

	void DestroyAllItems();

	void AddStateToAllItems(EItemState State);

private:

	void ChangeStateOfAllItems(EItemState itemState);
};
