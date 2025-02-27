// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/EnemyWeapon.h"
#include "Characters/ActorComponents/Inventory.h"
#include <Kismet/GameplayStatics.h>
#include "System/CorneredPlayerController.h"
#include "Perception/PawnSensingComponent.h"
#include "Configs/DataAssets/Config_AI.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"

const FName UEnemyWeapon::Target(TEXT("Target"));

UEnemyWeapon::UEnemyWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyWeapon::ManageDebugDrawings(bool enabled) {
	bDrawDebug = enabled;
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

			UStaticMeshComponent* TaggedComponent = Cast<UStaticMeshComponent>(pawn->FindComponentByTag(UStaticMeshComponent::StaticClass(), Target));

			FVector Direction = pawn->GetActorLocation() - Owner->GetActorLocation();
			Direction.Normalize();

			FShotRayDatas ShotRayDatas = GetShotRayDatas();

			FHitResult HitResult;

			bool bHit = GetWorld()->LineTraceSingleByChannel(
				HitResult,
				ShotRayDatas.Origin,
				TaggedComponent->GetComponentLocation(),
				GetOpponentTraceChannel()
			);

			DrawDebug(World, ShotRayDatas, TaggedComponent);

			if (bHit && HitResult.GetActor() == pawn && pawnSensing->CouldSeePawn(pawn)) {
				ShootWithEquippedWeapon();
			}
		}
	}
}

void UEnemyWeapon::DrawDebug(UWorld* World, FShotRayDatas ShotRayDatas, UStaticMeshComponent* TaggedComponent) {
	if (!bDrawDebug) {
		return;
	}

	DrawDebugLine(World, ShotRayDatas.Origin, TaggedComponent->GetComponentLocation(), FColor::Green, false, 1.0f, 0, 1.0f);
}

FShotRayDatas UEnemyWeapon::GetShotRayDatas() const {
	FShotRayDatas ShotDatas;

	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	UStaticMeshComponent* TaggedComponent = Cast<UStaticMeshComponent>(pawn->FindComponentByTag(UStaticMeshComponent::StaticClass(), Target));

	UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();

	FShotRayDatas ShotRayDatas = equipmentVisualizer->GetShotRayDatas();

	ShotDatas.Origin = ShotRayDatas.Origin;
	ShotDatas.End = TaggedComponent->GetComponentLocation();

	return ShotDatas;
}

ECollisionChannel UEnemyWeapon::GetOpponentTraceChannel() const {
	return ECC_GameTraceChannel3;
}