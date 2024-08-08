// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyWeapon.h"
#include "Inventory.h"
#include <Kismet/GameplayStatics.h>
#include <CorneredPlayerController.h>
#include "Perception/PawnSensingComponent.h"

EItemType UEnemyWeapon::GetEquippedWeapon() const {

	UInventory* inventory = Cast<UInventory>(GetOwner()->GetComponentByClass(UInventory::StaticClass()));
	return inventory->GetWeapon();
}

void UEnemyWeapon::BeginPlay() {

	Super::BeginPlay();
}

void UEnemyWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    if (bIsReadyToShoot)
    {
        UPawnSensingComponent* pawnSensing = Cast<UPawnSensingComponent>(GetOwner()->GetComponentByClass(UPawnSensingComponent::StaticClass()));

        if (pawnSensing)
        {
            APawn* pawn= UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

            if (pawnSensing->CouldSeePawn(pawn)) {
                ShootWithEquippedWeapon();
            }
        }
    }
}