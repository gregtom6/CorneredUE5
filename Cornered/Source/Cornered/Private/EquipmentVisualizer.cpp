// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentVisualizer.h"
#include "Config_Equipment.h"
#include "Product.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UEquipmentVisualizer::UEquipmentVisualizer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipmentVisualizer::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UEquipmentVisualizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentVisualizer::VisualizeEquipment(EItemType itemType) {
	TSubclassOf<AActor> product = ConfigEquipment->GetEquippedProduct(itemType);

	TObjectPtr<AActor> SpawnedActor = GetWorld()->SpawnActor<AActor>(product);

	ACharacter* character = Cast<ACharacter>(GetOwner());

	SpawnedActor->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightArmSocket"));
}
