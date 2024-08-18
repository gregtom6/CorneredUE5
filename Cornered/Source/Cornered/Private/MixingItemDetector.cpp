// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "MixingItemDetector.h"
#include "Components/ShapeComponent.h"
#include "Ingredient.h"

TArray<FItemData> AMixingItemDetector::GetDetectedItems() {
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

void AMixingItemDetector::BurnAllItems() {
	ChangeStateOfAllItems(EItemState::Burned);
}

void AMixingItemDetector::FreezeAllItems() {
	ChangeStateOfAllItems(EItemState::Freezed);
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