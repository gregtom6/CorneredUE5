// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "Items/Product.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "Items/WeaponProduct.h"
#include "Items/ShieldProduct.h"
#include "Items/AdditionalProduct.h"
#include "Items/EquippedWeapon.h"
#include "Characters/ActorComponents/CharacterWeapon.h"

const FName UEquipmentVisualizer::RightArmSocketPistol(TEXT("RightArmSocketPistol"));
const FName UEquipmentVisualizer::RightArmSocketShotgun(TEXT("RightArmSocketShotgun"));
const FName UEquipmentVisualizer::BodySocket(TEXT("BodySocket"));
const FName UEquipmentVisualizer::EmptyName(TEXT(""));

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

	ActualVisualization(Product->GetItemType(), GetNameOfSocket(Product));
}

void UEquipmentVisualizer::VisualizeWeaponDatas(FItemData ItemDatas) {

	ActualVisualization(ItemDatas.ItemType, GetNameOfSocketBasedOnItemType(ItemDatas.ItemType));
}

void UEquipmentVisualizer::ActualVisualization(EItemType ItemType, FName SocketName) {
	TSubclassOf<AActor> product = ConfigEquipment->GetEquippedProduct(ItemType);

	ACharacter* character = Cast<ACharacter>(GetOwner());

	SpawnedEquippedWeapon = GetWorld()->SpawnActor<AActor>(product);
	SpawnedEquippedWeapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);

	AEquippedWeapon* EquippedWeapon= Cast<AEquippedWeapon>(SpawnedEquippedWeapon);
	if (EquippedWeapon) {
		EquippedWeapon->SetEquipperActor(character);
	}

	bWeaponSpawned = true;
}

FName UEquipmentVisualizer::GetNameOfSocketBasedOnItemType(EItemType ItemType) const {
	if (ItemType == EItemType::Pistol) {
		return RightArmSocketPistol;
	}
	
	return RightArmSocketShotgun;
}

FName UEquipmentVisualizer::GetNameOfSocket(AProduct* Product) const {
	if (Product->IsA(AWeaponProduct::StaticClass())) {
		return GetNameOfSocketBasedOnItemType(Product->GetItemType());
	}
	else if (Product->IsA(AShieldProduct::StaticClass())) {
		return BodySocket;
	}
	else if (Product->IsA(AAdditionalProduct::StaticClass())) {
		return EmptyName;
	}

	return EmptyName;
}

void UEquipmentVisualizer::PlayEquippedWeaponVisuals() {
	AEquippedWeapon* equippedWeapon = Cast<AEquippedWeapon>(SpawnedEquippedWeapon);
	if (equippedWeapon) {
		equippedWeapon->ShotHappened();
	}
}

FShotRayDatas UEquipmentVisualizer::GetShotRayDatas() const {
	AEquippedWeapon* equippedWeapon = Cast<AEquippedWeapon>(SpawnedEquippedWeapon);
	return equippedWeapon->GetShotRayDatas();
}