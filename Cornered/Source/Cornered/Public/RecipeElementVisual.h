// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RecipeElementVisual.generated.h"

class UMaterialInterface;
class UPaperSpriteComponent;
class USceneComponent;

UCLASS()
class CORNERED_API ARecipeElementVisual : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecipeElementVisual();

public:	

	UFUNCTION()
		void SetElement(UMaterialInterface* ElementMaterial, UMaterialInterface* EffectMaterial);

private:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPaperSpriteComponent> ElementSprite;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPaperSpriteComponent> EffectSprite;
};
