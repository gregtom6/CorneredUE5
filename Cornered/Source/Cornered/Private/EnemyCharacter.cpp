// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <PlayerCharacterAnimInstance.h>
#include "EnemyWeapon.h"
#include "Camera/CameraComponent.h"
#include "EquipmentVisualizer.h"
#include "Components/SceneComponent.h"
#include "Inventory.h"
#include "PaperSpriteComponent.h"
#include "CooldownIndicator.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyHealth.h"
#include "EnemyController.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Config_Equipment.h"
#include "ExternalEquipper.h"
#include "Components/StateTreeComponent.h"
#include "HideSpotFinder.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyWeaponComp = CreateDefaultSubobject<UEnemyWeapon>(TEXT("EnemyWeaponComp"));

	CooldownIndicatorParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("CooldownIndicatorParentComp"));

	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComp"));

	CooldownIndicatorComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CooldownIndicatorComp"));

	EquipmentVisualizer = CreateDefaultSubobject<UEquipmentVisualizer>(TEXT("EquipmentVisualizer"));

	InventoryComp = CreateDefaultSubobject<UInventory>(TEXT("InventoryComp"));

	HideSpotFinderComp = CreateDefaultSubobject<UHideSpotFinder>(TEXT("HideSpotFinderComp"));

	ExternalEquipperComp = CreateDefaultSubobject<UExternalEquipper>(TEXT("ExternalEquipperComp"));

	EnemyHealthComp = CreateDefaultSubobject<UEnemyHealth>(TEXT("EnemyHealthComp"));

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	StateTreeComp = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComp"));

	CooldownIndicatorManagementComp = CreateDefaultSubobject<UCooldownIndicator>(TEXT("CooldownIndicatorManagementComp"));

	CameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CooldownIndicatorParentComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightArmSocket"));
	PaperSpriteComp->AttachToComponent(CooldownIndicatorParentComp, FAttachmentTransformRules::KeepRelativeTransform);
	CooldownIndicatorComp->AttachToComponent(PaperSpriteComp, FAttachmentTransformRules::KeepRelativeTransform);

	CooldownIndicatorParentComp->SetRelativeLocation(FVector(93.663588f, -25.109281f, -89.030848f));
	CooldownIndicatorParentComp->SetRelativeRotation(FRotator(-31.553031f, -16.355435f, -45.163447f));
	CooldownIndicatorParentComp->SetRelativeScale3D(FVector(20.0f, 20.0f, 49.375f));

	PaperSpriteComp->SetRelativeScale3D(FVector(1.0f, 1.684211f, 1.684211f));

	CooldownIndicatorComp->SetRelativeLocation(FVector(0.f, -0.1725f, 0.f));

	CooldownIndicatorManagementComp->SetComponents(CooldownIndicatorComp, EnemyWeaponComp);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AEnemyController* EnemyController = Cast<AEnemyController>(GetController());
	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (animInst) {
		if (EnemyController && animInst->LegState != (int)EnemyController->GetMovementState()) {
			animInst->LegState = (int)EnemyController->GetMovementState();
		}

		if (EnemyWeaponComp && animInst->UseWeapon != EnemyWeaponComp->IsThereEquippedWeapon()) {
			animInst->UseWeapon = EnemyWeaponComp->IsThereEquippedWeapon();
		}
	}
}

void AEnemyCharacter::SetEquipment(FItemDatas weapon, FItemDatas shield, FItemDatas additional) {
	ExternalEquipperComp->Equip(weapon, shield, additional);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (EnemyHealthComp)
	{
		EnemyHealthComp->DamageHealth(DamageAmount);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}