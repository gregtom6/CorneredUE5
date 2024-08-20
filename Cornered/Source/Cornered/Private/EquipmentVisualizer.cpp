// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EquipmentVisualizer.h"
#include "Config_Equipment.h"
#include "Product.h"
#include "PlayerCharacter.h"
#include "WeaponProduct.h"
#include "ShieldProduct.h"
#include "AdditionalProduct.h"
#include <EquippedWeapon.h>
#include "CharacterWeapon.h"

UEquipmentVisualizer::UEquipmentVisualizer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEquipmentVisualizer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Destroyed && SpawnedEquippedWeapon)
	{
		SpawnedEquippedWeapon->Destroy();
	}
}


// Called every frame
void UEquipmentVisualizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bWeaponSpawned) {
		UCharacterWeapon* characterWeapon = GetOwner()->FindComponentByClass<UCharacterWeapon>();
		characterWeapon->SetWeaponReadyToBeUsed();

		bWeaponSpawned = false;
	}
}

void UEquipmentVisualizer::VisualizeEquipment(AProduct* Product) {
	TSubclassOf<AActor> product = ConfigEquipment->GetEquippedProduct(Product->GetItemType());

	SpawnedEquippedWeapon = GetWorld()->SpawnActor<AActor>(product);

	APlayerCharacter* character = Cast<APlayerCharacter>(GetOwner());

	SpawnedEquippedWeapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, GetNameOfSocket(Product));

	//TODO: refactor:

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

void UEquipmentVisualizer::VisualizeWeaponDatas(FItemDatas ItemDatas) {
	TSubclassOf<AActor> product = ConfigEquipment->GetEquippedProduct(ItemDatas.Key);

	SpawnedEquippedWeapon = GetWorld()->SpawnActor<AActor>(product);

	ACharacter* character = Cast<ACharacter>(GetOwner());

	SpawnedEquippedWeapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightArmSocket"));

	//TODO: refactor:

	if (ItemDatas.Key == EItemType::Pistol) {
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

FName UEquipmentVisualizer::GetNameOfSocket(AProduct* Product) const {
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

FShotRayDatas UEquipmentVisualizer::GetShotRayDatas() const {
	AEquippedWeapon* equippedWeapon = Cast<AEquippedWeapon>(SpawnedEquippedWeapon);
	return equippedWeapon->GetShotRayDatas();
}