// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Ingredient.h"
#include "Components/StaticMeshComponent.h"
#include <Camera/CameraComponent.h>
#include "GameFramework/Actor.h"
#include <Picker.h>

// Sets default values
AIngredient::AIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void AIngredient::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->SetSimulatePhysics(true);
}

// Called every frame
void AIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngredient::Pickup(AActor* Actor) {

	StaticMesh->SetSimulatePhysics(false);

	UPicker* picker = Actor->GetComponentByClass<UPicker>();

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, true);

	AttachToComponent(picker, AttachmentRules);

	bWasPickedAnyTime = true;
}

void AIngredient::Drop() {
	StaticMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	StaticMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	StaticMesh->SetSimulatePhysics(true);
}

bool AIngredient::IsPicked() const {
	return !StaticMesh->IsSimulatingPhysics();
}

bool AIngredient::WasPickedAnytime() const {
	return bWasPickedAnyTime;
}

IEquippable* AIngredient::GetEquippable() const {
	return nullptr;
}

EItemType AIngredient::GetItemType() const {
	return ItemType;
}

EItemState AIngredient::GetItemState() const {
	return ItemState;
}

void AIngredient::SetState(EItemState itemState) {
	ItemState = itemState;
}