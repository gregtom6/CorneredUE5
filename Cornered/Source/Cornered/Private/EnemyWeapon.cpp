// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyWeapon.h"
#include "Inventory.h"
#include <Kismet/GameplayStatics.h>
#include <CorneredPlayerController.h>


EItemType UEnemyWeapon::GetEquippedWeapon() const {

	UInventory* inventory = Cast<UInventory>(GetOwner()->GetComponentByClass(UInventory::StaticClass()));
	return inventory->GetWeapon();
}

void UEnemyWeapon::BeginPlay() {

	Super::BeginPlay();
	/*
	AEnemyController* EnemyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ACorneredPlayerController* CustomPlayerController = Cast<ACorneredPlayerController>(PlayerController);
		if (CustomPlayerController)
		{
			CustomPlayerController->ShootHappenedInstance.AddUniqueDynamic(this, &UEnemyWeapon::ShootHappened);
		}
	}
	*/
}

void UEnemyWeapon::ShootHappened() {
	ShootWithEquippedWeapon();
}