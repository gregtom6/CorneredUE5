// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/EnemyWeapon.h"
#include "Characters/ActorComponents/Inventory.h"
#include <Kismet/GameplayStatics.h>
#include "System/CorneredPlayerController.h"
#include "Perception/PawnSensingComponent.h"

UEnemyWeapon::UEnemyWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	return;

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
				GetOpponentTraceChannel()
			);

			if (pawnSensing->CouldSeePawn(pawn)) {
				ShootWithEquippedWeapon();
			}
		}
	}
}

ECollisionChannel UEnemyWeapon::GetOpponentTraceChannel() const {
	return ECC_GameTraceChannel4;
}