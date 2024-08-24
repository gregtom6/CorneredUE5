// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CorneredCharacter.h"
#include "Camera/CameraComponent.h"
#include "EquipmentVisualizer.h"
#include "Components/SceneComponent.h"
#include "Inventory.h"
#include "PaperSpriteComponent.h"
#include "CooldownIndicator.h"
#include "CharacterHealth.h"
#include "CharacterAnimInstance.h"

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
}

// Called when the game starts or when spawned
void ACorneredCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CooldownIndicatorParentComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightArmSocket"));
	PaperSpriteComp->AttachToComponent(CooldownIndicatorParentComp, FAttachmentTransformRules::KeepRelativeTransform);
	CooldownIndicatorComp->AttachToComponent(PaperSpriteComp, FAttachmentTransformRules::KeepRelativeTransform);

	//TODO: refactor

	CooldownIndicatorParentComp->SetRelativeLocation(FVector(93.663588f, -25.109281f, -89.030848f));
	CooldownIndicatorParentComp->SetRelativeRotation(FRotator(-31.553031f, -16.355435f, -45.163447f));
	CooldownIndicatorParentComp->SetRelativeScale3D(FVector(20.0f, 20.0f, 49.375f));

	PaperSpriteComp->SetRelativeScale3D(FVector(1.0f, 1.684211f, 1.684211f));

	CooldownIndicatorComp->SetRelativeLocation(FVector(0.f, -0.1725f, 0.f));

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
	if (CharacterHealthComp)
	{
		CharacterHealthComp->DamageHealth(DamageAmount);
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}