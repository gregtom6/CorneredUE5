// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Config_Recipe.h"
#include "RecipeShower.generated.h"

class UMaterialInterface;
class UConfig_Recipe;
class USceneComponent;
class AGameModeBase;
class ARecipeElementVisual;

UCLASS()
class CORNERED_API ARecipeShower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARecipeShower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnNewMatchStarted();

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> StartingTransform;

	UPROPERTY(EditAnywhere)
		float HorizontalGapSize;

	UPROPERTY(EditAnywhere)
		float VerticalGapSize;

	UPROPERTY()
		TArray<TObjectPtr<AActor>> RecipeVisualElements;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Recipe> RecipeConfig;

	UFUNCTION()
		void GenerateRecipeVisuals();

	UFUNCTION()
		void DestroyElements();

	UFUNCTION()
		void CreateRecipeElement(UMaterialInterface* Material, UMaterialInterface* StateMaterial, FVector& PositionForGeneration);

	UFUNCTION()
		void AddOperatorIfNeeded(int32 Index, int32 MaterialCount, FVector& PositionForGeneration);

	UFUNCTION()
		bool IsIndexBeforeAlmostLastElement(int32 Index, int32 Count);

	UFUNCTION()
		bool IsIndexBeforeLastElement(int32 Index, int32 Count);

	UFUNCTION()
		void CreateOperator(UMaterialInterface* Material, FVector& PositionForGeneration);

	UFUNCTION()
		void MoveToNextRow(FVector& PositionForGeneration);

	UFUNCTION()
		void GenerateRecipeRow(FMaterialArray Materials, FMaterialArray StateMaterials, FVector& PositionForGeneration);

	UFUNCTION()
		void RecipeElementCreation(TSubclassOf<AActor> ClassOfElement, FVector& PositionForGeneration, UMaterialInterface* Material, float xDelta, UMaterialInterface* EffectMaterial = nullptr);
};
