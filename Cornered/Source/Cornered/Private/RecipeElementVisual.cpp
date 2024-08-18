// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "RecipeElementVisual.h"
#include "Materials/MaterialInterface.h"
#include "PaperSpriteComponent.h"

// Sets default values
ARecipeElementVisual::ARecipeElementVisual()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ElementSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ElementSprite"));

	EffectSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EffectSprite"));

	SetRootComponent(Root);

	ElementSprite->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	EffectSprite->AttachToComponent(ElementSprite, FAttachmentTransformRules::KeepRelativeTransform);
}

void ARecipeElementVisual::SetElement(UMaterialInterface* ElementMaterial, UMaterialInterface* EffectMaterial) {

	ElementSprite->SetMaterial(0, ElementMaterial);

	EffectSprite->SetMaterial(0, EffectMaterial);

	EffectSprite->SetVisibility(EffectMaterial != nullptr);
}