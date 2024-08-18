// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "PlayerWeapon.h"
#include "Inventory.h"
#include <Kismet/GameplayStatics.h>
#include <CorneredPlayerController.h>

EItemType UPlayerWeapon::GetEquippedWeapon() const {
	
	UInventory* inventory = Cast<UInventory>(GetOwner()->GetComponentByClass(UInventory::StaticClass()));
	return inventory->GetWeapon();
}

void UPlayerWeapon::BeginPlay() {

	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ACorneredPlayerController* CustomPlayerController = Cast<ACorneredPlayerController>(PlayerController);
		if (CustomPlayerController)
		{
			CustomPlayerController->ShootHappenedInstance.AddUniqueDynamic(this, &UPlayerWeapon::ShootHappened);
		}
	}
}

void UPlayerWeapon::ShootHappened() {
	ShootWithEquippedWeapon();
}

void UPlayerWeapon::InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) const {
	FVector Origin = shotRayDatas.Origin;

	FVector End = shotRayDatas.End;

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Origin,
		End,
		ECC_GameTraceChannel5
	);

	if (bHit) {

		UGameplayStatics::ApplyDamage(HitResult.GetActor(), weaponSettings.Damage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
	}
}