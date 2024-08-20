// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyWeapon.h"
#include "Inventory.h"
#include <Kismet/GameplayStatics.h>
#include <CorneredPlayerController.h>
#include "Perception/PawnSensingComponent.h"

UEnemyWeapon::UEnemyWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EItemType UEnemyWeapon::GetEquippedWeapon() const {

	UInventory* inventory = GetOwner()->FindComponentByClass<UInventory>();
	return inventory->GetWeapon();
}

void UEnemyWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if (bIsReadyToShoot)
	{
		UPawnSensingComponent* pawnSensing = GetOwner()->FindComponentByClass<UPawnSensingComponent>();

		if (pawnSensing)
		{
			APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);


			FVector Direction = pawn->GetActorLocation() - GetOwner()->GetActorLocation();

			float Distance = 1000.f;
			Direction.Normalize();

			FVector Origin = GetOwner()->GetActorLocation();

			FVector End = Origin + (Direction * Distance);

			FHitResult HitResult;

			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Origin,
				End,
				ECC_GameTraceChannel4
			);


			if (pawnSensing->CouldSeePawn(pawn)) {
				ShootWithEquippedWeapon();
			}
		}
	}
}

void UEnemyWeapon::InflictDamage(FWeaponSettingsEntry weaponSettings, FShotRayDatas shotRayDatas) const {
	FVector Origin = shotRayDatas.Origin;

	FVector End = shotRayDatas.End;

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Origin,
		End,
		ECC_GameTraceChannel4
	);

	if (bHit) {

		UGameplayStatics::ApplyDamage(HitResult.GetActor(), weaponSettings.Damage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
	}
}