// Fill out your copyright notice in the Description page of Project Settings.


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

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerWeaponComp = CreateDefaultSubobject<UPlayerWeapon>(TEXT("PlayerWeaponComp"));
	InteractableDetectorComp = CreateDefaultSubobject<UInteractableDetector>(TEXT("InteractableDetectorComp"));
	PickerComp = CreateDefaultSubobject<UPicker>(TEXT("PickerComp"));
	EquipperComp = CreateDefaultSubobject<UEquipper>(TEXT("EquipperComp"));

	CooldownIndicatorParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("CooldownIndicatorParentComp"));

	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComp"));

	CooldownIndicatorComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CooldownIndicatorComp"));


	EquipmentVisualizer = CreateDefaultSubobject<UEquipmentVisualizer>(TEXT("EquipmentVisualizer"));

	InventoryComp = CreateDefaultSubobject<UInventory>(TEXT("InventoryComp"));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	CooldownIndicatorComp->AttachToComponent(PaperSpriteComp, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);

	InteractableDetectorComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	PickerComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	EquipperComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CooldownIndicatorParentComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightArmSocket"));
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

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

