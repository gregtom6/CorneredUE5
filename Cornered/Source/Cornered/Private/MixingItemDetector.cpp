// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingItemDetector.h"
#include "Components/ShapeComponent.h"
#include "Ingredient.h"

AMixingItemDetector::AMixingItemDetector() {

}

TArray<EItemType> AMixingItemDetector::GetDetectedItems() {
	TArray<AActor*> OverlappingActors;
	GetCollisionComponent()->GetOverlappingActors(OverlappingActors);

	TArray<EItemType> itemTypes;

	for (int i = 0; i < OverlappingActors.Num(); i++) {
		AIngredient* ingredient = Cast<AIngredient>(OverlappingActors[i]);
		if (ingredient) {
			itemTypes.Add(ingredient->GetItemType());
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