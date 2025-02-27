// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/MixingMachine/MixingItemDetector.h"
#include "Components/ShapeComponent.h"
#include "Items/Ingredient.h"

TArray<FItemData> AMixingItemDetector::GetDetectedItems() const {
	TArray<AActor*> OverlappingActors;
	GetCollisionComponent()->GetOverlappingActors(OverlappingActors);

	TArray<FItemData> itemTypes;

	for (int i = 0; i < OverlappingActors.Num(); i++) {
		AIngredient* ingredient = Cast<AIngredient>(OverlappingActors[i]);
		if (ingredient) {
			FItemData data;
			data.ItemType = ingredient->GetItemType();
			data.ItemState = ingredient->GetItemState();
			itemTypes.Add(data);
		}
	}

	return itemTypes;
}

bool AMixingItemDetector::AreThereDetectedItems() {
	return GetDetectedItems().Num() > 0;
}

void AMixingItemDetector::DestroyAllItems() {
	TArray<AActor*> OverlappingActors;
	GetCollisionComponent()->GetOverlappingActors(OverlappingActors);

	for (int i = 0; i < OverlappingActors.Num(); i++) {
		AIngredient* ingredient = Cast<AIngredient>(OverlappingActors[i]);
		if (ingredient) {
			ingredient->Destroy();
		}
	}
}

void AMixingItemDetector::AddStateToAllItems(EItemState State) {
	ChangeStateOfAllItems(State);
}

void AMixingItemDetector::ChangeStateOfAllItems(EItemState itemState) {
	TArray<AActor*> OverlappingActors;
	GetCollisionComponent()->GetOverlappingActors(OverlappingActors);

	for (int i = 0; i < OverlappingActors.Num(); i++) {
		AIngredient* ingredient = Cast<AIngredient>(OverlappingActors[i]);
		if (ingredient) {
			ingredient->SetState(itemState);
		}
	}
}