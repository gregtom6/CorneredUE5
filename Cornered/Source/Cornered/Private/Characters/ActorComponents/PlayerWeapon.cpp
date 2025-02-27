// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/PlayerWeapon.h"
#include "Characters/ActorComponents/Inventory.h"
#include <Kismet/GameplayStatics.h>
#include "System/CorneredPlayerController.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Characters/ActorComponents/InteractableDetector.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"

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

	InteractableDetectorComp = GetOwner()->FindComponentByClass<UInteractableDetector>();
}

void UPlayerWeapon::ShootHappened() {

	if (HealthComp->GetCurrentHealth() <= 0.f) {
		return;
	}

	if (InteractableDetectorComp && InteractableDetectorComp->ItWasValidHit())
	{
		return;
	}

	ShootWithEquippedWeapon();
}

FShotRayDatas UPlayerWeapon::GetShotRayDatas() const {
	UEquipmentVisualizer* equipmentVisualizer = GetOwner()->FindComponentByClass<UEquipmentVisualizer>();

	return equipmentVisualizer->GetShotRayDatas();
}

ECollisionChannel UPlayerWeapon::GetOpponentTraceChannel() const {
	return ECC_GameTraceChannel5;
}