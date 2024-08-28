// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Characters/Systems/PlayerCharacterAnimInstance.h"
#include "Characters/ActorComponents/EnemyWeapon.h"
#include "PaperSpriteComponent.h"
#include "Characters/ActorComponents/CooldownIndicator.h"
#include "Perception/PawnSensingComponent.h"
#include "Characters/ActorComponents/EnemyHealth.h"
#include "Characters/Systems/EnemyController.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "Characters/ActorComponents/ExternalEquipper.h"
#include "Components/StateTreeComponent.h"
#include "Characters/ActorComponents/HideSpotFinder.h"
#include "Characters/Systems/CharacterAnimInstance.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterWeaponComp = CreateDefaultSubobject<UEnemyWeapon>(TEXT("EnemyWeaponComp"));
	HideSpotFinderComp = CreateDefaultSubobject<UHideSpotFinder>(TEXT("HideSpotFinderComp"));
	ExternalEquipperComp = CreateDefaultSubobject<UExternalEquipper>(TEXT("ExternalEquipperComp"));
	CharacterHealthComp = CreateDefaultSubobject<UEnemyHealth>(TEXT("EnemyHealthComp"));
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	StateTreeComp = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComp"));
}

void AEnemyCharacter::SetEquipment(FItemDatas weapon, FItemDatas shield, FItemDatas additional) {
	ExternalEquipperComp->Equip(weapon, shield, additional);
}

IMovableCharacter* AEnemyCharacter::GetOwnedController() const {
	AEnemyController* EnemyController = Cast<AEnemyController>(GetController());
	return EnemyController;
}

UCharacterAnimInstance* AEnemyCharacter::GetOwnedAnimInstance() const {
	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	return animInst;
}