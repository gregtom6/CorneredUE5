// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Items/Product.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Characters/ActorComponents/Inventory.h"
#include <Kismet/GameplayStatics.h>
#include "Camera/CameraComponent.h"
#include "Configs/DataAssets/Config_Equipment.h"

AProduct::AProduct() {
	PrimaryActorTick.bCanEverTick = true;

	bCanFlyIntoEquipper = false;
}

void AProduct::Equip(UEquipmentVisualizer* equipmentVisualizer, UInventory* inventory, UCameraComponent* camera, UConfig_Equipment* EquipmentConfig)
{
	StartTime= UGameplayStatics::GetTimeSeconds(GetWorld());

	EquipperCamera = camera;

	bCanFlyIntoEquipper = true;

	Config = EquipmentConfig;
}

IEquippable* AProduct::GetEquippable() const {
	return const_cast<IEquippable*>(static_cast<const IEquippable*>(this));
}

void AProduct::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!bCanFlyIntoEquipper) {
		return;
	}

	StartPosition = GetActorLocation();
	TargetPosition = EquipperCamera->GetComponentLocation();

	float actualTime = UGameplayStatics::GetTimeSeconds(GetWorld()) - StartTime;
	float actualPercentage = actualTime / Config->EquipTimeInSeconds;

	if (actualPercentage >= Config->PercentageOfEquipPath) {
		ArrivedIntoEquipper();
		return;
	}

	FVector NewPosition = FMath::Lerp(StartPosition, TargetPosition, actualPercentage);

	SetActorLocation(NewPosition);
}

void AProduct::ArrivedIntoEquipper() {

	ProductEquipEnded.Broadcast();

	Destroy();
}