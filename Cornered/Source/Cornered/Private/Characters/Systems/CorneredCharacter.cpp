// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/CorneredCharacter.h"
#include "Camera/CameraComponent.h"
#include "Characters/ActorComponents/EquipmentVisualizer.h"
#include "Components/SceneComponent.h"
#include "Characters/ActorComponents/Inventory.h"
#include "PaperSpriteComponent.h"
#include "Characters/ActorComponents/CooldownIndicator.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Characters/Systems/CharacterAnimInstance.h"

// Sets default values
ACorneredCharacter::ACorneredCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CooldownIndicatorParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("CooldownIndicatorParentComp"));
	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComp"));
	CooldownIndicatorComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CooldownIndicatorComp"));
	EquipmentVisualizer = CreateDefaultSubobject<UEquipmentVisualizer>(TEXT("EquipmentVisualizer"));
	InventoryComp = CreateDefaultSubobject<UInventory>(TEXT("InventoryComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CooldownIndicatorManagementComp = CreateDefaultSubobject<UCooldownIndicator>(TEXT("CooldownIndicatorManagementComp"));

	CameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	CooldownIndicatorParentComp->SetupAttachment(GetMesh(), FName("RightArmSocketCooldown"));
	PaperSpriteComp->AttachToComponent(CooldownIndicatorParentComp, FAttachmentTransformRules::KeepRelativeTransform);
	CooldownIndicatorComp->AttachToComponent(PaperSpriteComp, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACorneredCharacter::BeginPlay()
{
	Super::BeginPlay();

	CooldownIndicatorManagementComp->SetComponents(CooldownIndicatorComp, CharacterWeaponComp);
}

// Called every frame
void ACorneredCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IMovableCharacter* thisController = GetOwnedController();
	UCharacterAnimInstance* thisAnimInstance = GetOwnedAnimInstance();
	
	if (thisAnimInstance) {
		if (thisController && thisAnimInstance->LegState != (int)thisController->GetMovementState()) {
			thisAnimInstance->LegState = (int)thisController->GetMovementState();
		}

		if (CharacterWeaponComp && thisAnimInstance->UseWeapon != CharacterWeaponComp->IsThereEquippedWeapon()) {
			thisAnimInstance->UseWeapon = CharacterWeaponComp->IsThereEquippedWeapon();
		}
	}
}

float ACorneredCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CharacterHealth)
	{
		CharacterHealth->DamageHealth(DamageAmount);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ACorneredCharacter::SetDieState() {
	GetMesh()->SetSimulatePhysics(true);
}