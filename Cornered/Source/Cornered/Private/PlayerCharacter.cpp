// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "CorneredPlayerController.h"
#include <PlayerCharacterAnimInstance.h>
#include "InteractableDetector.h"
#include "Picker.h"
#include "Equipper.h"
#include "PlayerWeapon.h"
#include "Camera/CameraComponent.h"
#include "EquipmentVisualizer.h"
#include "Components/SceneComponent.h"
#include "Inventory.h"
#include "PaperSpriteComponent.h"
#include "CooldownIndicator.h"
#include "Interactor.h"
#include "Components/AudioComponent.h"
#include "PlayerHealth.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerWeaponComp = CreateDefaultSubobject<UPlayerWeapon>(TEXT("PlayerWeaponComp"));
	InteractableDetectorComp = CreateDefaultSubobject<UInteractableDetector>(TEXT("InteractableDetectorComp"));
	PickerComp = CreateDefaultSubobject<UPicker>(TEXT("PickerComp"));
	EquipperComp = CreateDefaultSubobject<UEquipper>(TEXT("EquipperComp"));
	InteractorComp = CreateDefaultSubobject<UInteractor>(TEXT("InteractorComp"));

	CooldownIndicatorParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("CooldownIndicatorParentComp"));

	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComp"));

	CooldownIndicatorComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CooldownIndicatorComp"));

	EquipAudio= CreateDefaultSubobject<UAudioComponent>(TEXT("EquipAudio"));

	EquipmentVisualizer = CreateDefaultSubobject<UEquipmentVisualizer>(TEXT("EquipmentVisualizer"));

	InventoryComp = CreateDefaultSubobject<UInventory>(TEXT("InventoryComp"));

	PlayerHealthComp = CreateDefaultSubobject<UPlayerHealth>(TEXT("PlayerHealthComp"));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	CooldownIndicatorManagementComp = CreateDefaultSubobject<UCooldownIndicator>(TEXT("CooldownIndicatorManagementComp"));

	CameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	InteractableDetectorComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	PickerComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	EquipperComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	InteractorComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);

	EquipAudio->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CooldownIndicatorParentComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightArmSocket"));
	PaperSpriteComp->AttachToComponent(CooldownIndicatorParentComp, FAttachmentTransformRules::KeepRelativeTransform);
	CooldownIndicatorComp->AttachToComponent(PaperSpriteComp, FAttachmentTransformRules::KeepRelativeTransform);

	CooldownIndicatorParentComp->SetRelativeLocation(FVector(93.663588f, -25.109281f, -89.030848f));
	CooldownIndicatorParentComp->SetRelativeRotation(FRotator(-31.553031f, -16.355435f, -45.163447f ));
	CooldownIndicatorParentComp->SetRelativeScale3D(FVector(20.0f, 20.0f, 49.375f));

	PaperSpriteComp->SetRelativeScale3D(FVector(1.0f, 1.684211f, 1.684211f));

	CooldownIndicatorComp->SetRelativeLocation(FVector(0.f, -0.1725f, 0.f));

	CooldownIndicatorManagementComp->SetComponents(CooldownIndicatorComp, PlayerWeaponComp);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ACorneredPlayerController* CorneredPlayerController = Cast<ACorneredPlayerController>(PlayerController);
	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (animInst) {
		if (CorneredPlayerController && animInst->LegState != (int)CorneredPlayerController->GetMovementState()) {
			animInst->LegState = (int)CorneredPlayerController->GetMovementState();
		}

		if (PlayerWeaponComp && animInst->UseWeapon != PlayerWeaponComp->IsThereEquippedWeapon()) {
			animInst->UseWeapon = PlayerWeaponComp->IsThereEquippedWeapon();
		}
	}
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Pass damage to the health component
	if (PlayerHealthComp)
	{
		PlayerHealthComp->DamageHealth(DamageAmount);
	}

	// Call base class implementation
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}