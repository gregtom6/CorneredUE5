// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "System/CorneredPlayerController.h"
#include "Characters/Systems/PlayerCharacterAnimInstance.h"
#include "Characters/ActorComponents/InteractableDetector.h"
#include "Characters/ActorComponents/Picker.h"
#include "Characters/ActorComponents/Equipper.h"
#include "Characters/ActorComponents/PlayerWeapon.h"
#include "Camera/CameraComponent.h"
#include "Characters/ActorComponents/Interactor.h"
#include "Components/AudioComponent.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Characters/Systems/CharacterAnimInstance.h"
#include "Characters/ActorComponents/PostProcessController.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Configs/DataAssets/Config_Time.h"

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
	DeathAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathAudio"));
	CharacterHealth = CreateDefaultSubobject<UCharacterHealth>(TEXT("HealthComp"));
	PostProcessController = CreateDefaultSubobject<UPostProcessController>(TEXT("PostProcessComp"));

	InteractableDetectorComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	PickerComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	EquipperComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	InteractorComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	EquipAudio->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	DeathAudio->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterHealth->CharacterDefeated.AddUniqueDynamic(this, &APlayerCharacter::OnCharacterDefeated);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bCharacterDied) {
		return;
	}

	float currentTime = GetWorld()->GetTimeSeconds() - TimeWhenCharacterDied;
	float percentage = currentTime / TimeConfig->WaitTimeUntilGameOver;
	percentage = FMath::Clamp(percentage, 0.f, 1.f);
	DeathAudio->SetVolumeMultiplier(percentage);
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

void APlayerCharacter::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {

	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {
		return;
	}

	bCharacterDied = true;
	TimeWhenCharacterDied= GetWorld()->GetTimeSeconds();

	DeathAudio->Play();
}