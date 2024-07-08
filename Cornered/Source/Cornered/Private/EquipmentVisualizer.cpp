// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentVisualizer.h"
#include "Config_Equipment.h"
#include "Product.h"
#include "PlayerCharacter.h"
#include "WeaponProduct.h"
#include "ShieldProduct.h"
#include "AdditionalProduct.h"
#include <EquippedWeapon.h>
#include "CharacterWeapon.h"

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

	if (bWeaponSpawned) {
		UCharacterWeapon* characterWeapon = Cast<UCharacterWeapon>(GetOwner()->GetComponentByClass(UCharacterWeapon::StaticClass()));
		characterWeapon->SetWeaponReadyToBeUsed();

		bWeaponSpawned = false;
	}
}

void UEquipmentVisualizer::VisualizeEquipment(AProduct* Product) {
	TSubclassOf<AActor> product = ConfigEquipment->GetEquippedProduct(Product->GetItemType());

	SpawnedEquippedWeapon = GetWorld()->SpawnActor<AActor>(product);

	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());

	SpawnedEquippedWeapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, GetNameOfSocket(Product));

	if (Product->GetItemType() == EItemType::Pistol) {
		SpawnedEquippedWeapon->SetActorRelativeLocation(FVector(189.0f, 210.0f, 145.0f));
		SpawnedEquippedWeapon->SetActorRelativeRotation(FRotator(-48.496153f, -51.800591f, -4.977581f));
	}
	else {
		SpawnedEquippedWeapon->SetActorRelativeLocation(FVector(442.129621f, 23.534655f, 282.048388f));
		SpawnedEquippedWeapon->SetActorRelativeRotation(FRotator(-48.496153f, -51.800591f, -4.977581f));
		SpawnedEquippedWeapon->SetActorRelativeScale3D(FVector(0.5775f, 0.5775f, 0.5775f));
	}

	bWeaponSpawned = true;
}

FName UEquipmentVisualizer::GetNameOfSocket(AProduct* Product) {
	if (Product->IsA(AWeaponProduct::StaticClass())) {
		return FName("RightArmSocket");
	}
	else if (Product->IsA(AShieldProduct::StaticClass())) {
		return FName("BodySocket");
	}
	else if (Product->IsA(AAdditionalProduct::StaticClass())) {
		return FName("");
	}

	return FName("");
}

void UEquipmentVisualizer::PlayEquippedWeaponVisuals() {
	AEquippedWeapon* equippedWeapon = Cast<AEquippedWeapon>(SpawnedEquippedWeapon);
	if (equippedWeapon) {
		equippedWeapon->SetEquipperActor(GetOwner());
		equippedWeapon->ShotHappened();
	}
}