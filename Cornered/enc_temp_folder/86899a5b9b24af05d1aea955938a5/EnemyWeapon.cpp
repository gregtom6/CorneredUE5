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

			//FVector Origin = Owner->GetActorLocation();
			//FVector End = Origin + (Direction * AIConfig->EnemyAttackVisionDistance);

			TArray<FHitResult> HitResult;

			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(GetOpponentTraceChannel()));         
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));  
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic)); 
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_PhysicsBody));

			bool bHit = World->LineTraceMultiByObjectType(
				HitResult,
				ShotRayDatas.Origin,
				ShotRayDatas.End,
				FCollisionObjectQueryParams(ObjectTypes)
			);

			if (bHit && HitResult[0].GetActor() == pawn && pawnSensing->CouldSeePawn(pawn)) {
				ShootWithEquippedWeapon();
			}
		}
	}
}

ECollisionChannel UEnemyWeapon::GetOpponentTraceChannel() const {
	return ECC_GameTraceChannel3;
}