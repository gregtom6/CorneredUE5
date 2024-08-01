// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "RecipeElementVisual.h"
#include "Materials/MaterialInterface.h"
#include "PaperSpriteComponent.h"

// Sets default values
ARecipeElementVisual::ARecipeElementVisual()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ElementSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ElementSprite"));

	EffectSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EffectSprite"));

	SetRootComponent(Root);

	ElementSprite->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	EffectSprite->AttachToComponent(ElementSprite, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ARecipeElementVisual::BeginPlay()
{
	Super::BeginPlay();

	SetVisualComponents();
}

// Called every frame
void ARecipeElementVisual::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARecipeElementVisual::SetElement(UMaterialInterface* ElementMaterial, UMaterialInterface* EffectMaterial) {

	ElementMaterialToUse = ElementMaterial;
	EffectMaterialToUse = EffectMaterial;

	SetVisualComponents();
}

void ARecipeElementVisual::SetVisualComponents() {

	ElementSprite->SetMaterial(0, ElementMaterialToUse);

	EffectSprite->SetMaterial(0, EffectMaterialToUse);

	EffectSprite->SetVisibility(EffectMaterialToUse != nullptr);
}