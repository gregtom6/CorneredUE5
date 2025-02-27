// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/MixingMachine/MixingMachineAbility.h"
#include "Environment/Interactables/CorneredButton.h"
#include "System/ProgressionGameState.h"
#include "Environment/MixingMachine/MixingItemDetector.h"
#include "Items/Ingredient.h"
#include "Configs/DataAssets/Config_Recipe.h"

// Sets default values for this component's properties
UMixingMachineAbility::UMixingMachineAbility()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMixingMachineAbility::BeginPlay() {
	Super::BeginPlay();

	AbilityButton->PressHappened.AddUniqueDynamic(this, &UMixingMachineAbility::AbilityPressHappened);
}

void UMixingMachineAbility::AbilityPressHappened() {
	AbilityActivated.Broadcast(this);
}

void UMixingMachineAbility::AbilityTimeEnded(AMixingItemDetector* MixingItemDetector, UConfig_Recipe* RecipeConfig, FVector ResultLocation) {

	ResultCreation(MixingItemDetector, RecipeConfig, ResultLocation);

	AddingEffectOnItems(MixingItemDetector);
}

void UMixingMachineAbility::SetButtonStatus() {
	AProgressionGameState* GameState = GetWorld()->GetGameState<AProgressionGameState>();

	AbilityButton->SetActorHiddenInGame(!GameState->IsAbilityAlreadyUnlocked(AbilityType));
}

float UMixingMachineAbility::GetCurrentProcessTime() const {
	return MixingMachineConfig->GetProcessTime(AbilityType);
}

void UMixingMachineAbility::ResultCreation(AMixingItemDetector* MixingItemDetector, UConfig_Recipe* RecipeConfig, FVector ResultLocation) {

	if (!IsThereCreationResult(MixingItemDetector, RecipeConfig)) {
		return;
	}

	TArray<FItemData> detectedItems = MixingItemDetector->GetDetectedItems();

	TSubclassOf<AIngredient> result = RecipeConfig->GetResultItem(detectedItems);

	if (result)
	{
		GetWorld()->SpawnActor<AActor>(result, ResultLocation, FRotator::ZeroRotator);
		MixingItemDetector->DestroyAllItems();
	}
}

void UMixingMachineAbility::AddingEffectOnItems(AMixingItemDetector* MixingItemDetector) {
	if (!bShouldAddEffect) {
		return;
	}

	MixingItemDetector->AddStateToAllItems(ItemStateAfterAbility);
}

bool UMixingMachineAbility::IsThereCreationResult(AMixingItemDetector* MixingItemDetector, UConfig_Recipe* RecipeConfig) {
	if (!bShouldCreateResult) {
		return false;
	}

	if (!MixingItemDetector->AreThereDetectedItems())
	{
		return false;
	}

	TArray<FItemData> detectedItems = MixingItemDetector->GetDetectedItems();

	TSubclassOf<AIngredient> result = RecipeConfig->GetResultItem(detectedItems);

	return result != nullptr;
}