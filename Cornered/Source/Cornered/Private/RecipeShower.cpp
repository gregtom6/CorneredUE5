// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "RecipeShower.h"
#include "Materials/MaterialInterface.h"
#include "Config_Recipe.h"
#include "Components/SceneComponent.h"
#include "CorneredGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "RecipeElementVisual.h"

// Sets default values
ARecipeShower::ARecipeShower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	StartingTransform = CreateDefaultSubobject<USceneComponent>(TEXT("StartingTransform"));

	StartingTransform->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ARecipeShower::BeginPlay()
{
	Super::BeginPlay();

	DestroyElements();
	GenerateRecipeVisuals();
}

// Called every frame
void ARecipeShower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARecipeShower::DestroyElements() {
	for (int32 i = 0; i < RecipeVisualElements.Num(); i++) {
		RecipeVisualElements[i]->Destroy();
	}

	RecipeVisualElements.Empty();
}


void ARecipeShower::GenerateRecipeVisuals() {
	FVector PositionForGeneration = StartingTransform->GetComponentLocation();

	TArray<FMaterialArray> StateMaterials;

	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	UGameInstance* GameInstance = GameMode->GetGameInstance();

	UCorneredGameInstance* CorneredGameInstance = Cast<UCorneredGameInstance>(GameInstance);

	TArray<FMaterialArray> Materials = RecipeConfig->GetRadiatingMaterialsOfAllRecipes(StateMaterials, CorneredGameInstance);

	for (int currentRow = 0; currentRow < Materials.Num(); currentRow++) {

		GenerateRecipeRow(Materials[currentRow], StateMaterials[currentRow], PositionForGeneration);
		MoveToNextRow(PositionForGeneration);
	}
}

void ARecipeShower::CreateRecipeElement(UMaterialInterface* Material, UMaterialInterface* StateMaterial, FVector& PositionForGeneration) {
	RecipeElementCreation(RecipeConfig->RecipeShowElementClass, PositionForGeneration, Material, HorizontalGapSize, StateMaterial);
}

void ARecipeShower::AddOperatorIfNeeded(int index, int materialCount, FVector& PositionForGeneration) {
	if (IsIndexBeforeAlmostLastElement(index, materialCount)) {
		CreateOperator(RecipeConfig->RecipeShowPlusMaterial, PositionForGeneration);
	}
	else if (IsIndexBeforeLastElement(index, materialCount)) {
		CreateOperator(RecipeConfig->RecipeShowEqualMaterial, PositionForGeneration);
	}
}

bool ARecipeShower::IsIndexBeforeAlmostLastElement(int index, int count) {
	return index + 2 < count;
}

bool ARecipeShower::IsIndexBeforeLastElement(int index, int count) {
	return index + 1 < count;
}

void ARecipeShower::CreateOperator(UMaterialInterface* operatorMaterial, FVector& PositionForGeneration) {
	RecipeElementCreation(RecipeConfig->RecipeShowOperatorClass, PositionForGeneration, operatorMaterial, HorizontalGapSize);
}

void ARecipeShower::MoveToNextRow(FVector& PositionForGeneration) {
	PositionForGeneration = FVector(StartingTransform->GetComponentLocation().X, PositionForGeneration.Y, PositionForGeneration.Z + VerticalGapSize);
}

void ARecipeShower::GenerateRecipeRow(FMaterialArray Materials, FMaterialArray StateMaterials, FVector& PositionForGeneration) {
	for (int currentColumn = 0; currentColumn < Materials.Materials.Num(); currentColumn++) {
		CreateRecipeElement(Materials.Materials[currentColumn], StateMaterials.Materials[currentColumn], PositionForGeneration);
		AddOperatorIfNeeded(currentColumn, Materials.Materials.Num(), PositionForGeneration);
	}
}

void ARecipeShower::RecipeElementCreation(TSubclassOf<AActor> RecipeElementClass, FVector& PositionForGeneration, UMaterialInterface* ElementMaterial, float xDelta, UMaterialInterface* EffectMaterial) {
	UWorld* world = GetWorld();

	ARecipeElementVisual* recipeElement = world->SpawnActor<ARecipeElementVisual>(RecipeElementClass, PositionForGeneration, FRotator::ZeroRotator);
	RecipeVisualElements.Add(recipeElement);

	ARecipeElementVisual* RecipeElementVisual = Cast<ARecipeElementVisual>(recipeElement);

	RecipeElementVisual->SetElement(ElementMaterial, EffectMaterial);

	recipeElement->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	PositionForGeneration = FVector(PositionForGeneration.X - xDelta, PositionForGeneration.Y, PositionForGeneration.Z);
}