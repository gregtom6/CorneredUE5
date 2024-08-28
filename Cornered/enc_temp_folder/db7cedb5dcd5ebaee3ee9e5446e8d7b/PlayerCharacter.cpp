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
#include "Interactor.h"
#include "Components/AudioComponent.h"
#include "PlayerHealth.h"
#include "CharacterAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterWeaponComp = CreateDefaultSubobject<UPlayerWeapon>(TEXT("PlayerWeaponComp"));
	InteractableDetectorComp = CreateDefaultSubobject<UInteractableDetector>(TEXT("InteractableDetectorComp"));
	PickerComp = CreateDefaultSubobject<UPicker>(TEXT("PickerComp"));
	EquipperComp = CreateDefaultSubobject<UEquipper>(TEXT("EquipperComp"));
	InteractorComp = CreateDefaultSubobject<UInteractor>(TEXT("InteractorComp"));

	EquipAudio= CreateDefaultSubobject<UAudioComponent>(TEXT("EquipAudio"));

	CharacterHealthComp = CreateDefaultSubobject<UPlayerHealth>(TEXT("PlayerHealthComp"));

	InteractableDetectorComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	PickerComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	EquipperComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	InteractorComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);

	EquipAudio->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
}

IMovableCharacter* APlayerCharacter::GetOwnedController() const {
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ACorneredPlayerController* CorneredPlayerController = Cast<ACorneredPlayerController>(PlayerController);
	return CorneredPlayerController;
}

UCharacterAnimInstance* APlayerCharacter::GetOwnedAnimInstance() const {
	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	return animInst;
}