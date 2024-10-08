// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/EnemyWeapon.h"
#include "Characters/ActorComponents/Inventory.h"
#include <Kismet/GameplayStatics.h>
#include "System/CorneredPlayerController.h"
#include "Perception/PawnSensingComponent.h"
#include "Configs/DataAssets/Config_AI.h"
#include "Characters/ActorComponents/CharacterHealth.h"

UEnemyWeapon::UEnemyWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	if (HealthComp->GetCurrentHealth() <= 0.f) {
		return;
	}

	if (bIsReadyToShoot)
	{
		AActor* Owner = GetOwner();
		UWorld* World = GetWorld();

		UPawnSensingComponent* pawnSensing = Owner->FindComponentByClass<UPawnSensingComponent>();

		if (pawnSensing)
		{
			APawn* pawn = UGameplayStatics::GetPlayerPawn(World, 0);

			FVector Direction = pawn->GetActorLocation() - Owner->GetActorLocation();
			Direction.Normalize();

			FShotRayDatas ShotRayDatas = GetShotRayDatas();

			FHitResult HitResult;

			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				ShotRayDatas.Origin,
				ShotRayDatas.End,
				GetOpponentTraceChannel()
			);

			DrawDebugLine(World, ShotRayDatas.Origin, ShotRayDatas.End, FColor::Green, false, 1.0f, 0, 1.0f);

			if (bHit && HitResult.GetActor() == pawn && pawnSensing->CouldSeePawn(pawn)) {
				ShootWithEquippedWeapon();
			}
		}
	}
}

ECollisionChannel UEnemyWeapon::GetOpponentTraceChannel() const {
	return ECC_GameTraceChannel3;
}