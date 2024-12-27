// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Characters/Systems/PlayerCharacterAnimInstance.h"
#include "Characters/ActorComponents/EnemyWeapon.h"
#include "PaperSpriteComponent.h"
#include "Characters/ActorComponents/CooldownIndicator.h"
#include "Perception/PawnSensingComponent.h"
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
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Characters/ActorComponents/InteractableDetector.h"
#include "Components/AudioComponent.h"
#include "CableComponent.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInterface.h"
#include "Configs/DataAssets/Config_DamageVisual.h"
#include "Components/SceneComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterWeaponComp = CreateDefaultSubobject<UEnemyWeapon>(TEXT("EnemyWeaponComp"));
	HideSpotFinderComp = CreateDefaultSubobject<UHideSpotFinder>(TEXT("HideSpotFinderComp"));
	ExternalEquipperComp = CreateDefaultSubobject<UExternalEquipper>(TEXT("ExternalEquipperComp"));
	CharacterHealth = CreateDefaultSubobject<UCharacterHealth>(TEXT("HealthComp"));
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	StateTreeComp = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComp"));
	DieAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("DieAudio"));

	ScreamAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ScreamAudio"));
	DamageAlarmAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("DamageAlarmAudio"));
	ExplosionAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplosionAudio"));

	CableComp1 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon1"));
	CableComp2 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon2"));
	CableComp3 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon3"));
	CableComp4 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon4"));

	CableNiagaraComp1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CableNiagaraComp1"));
	CableNiagaraComp2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CableNiagaraComp2"));
	CableNiagaraComp3 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CableNiagaraComp3"));
	CableNiagaraComp4 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CableNiagaraComp4"));

	DeathNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DeathNiagara"));

	SoulLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SoulLocation"));

	USceneComponent* SceneComponent = Cast<USceneComponent>(GetCapsuleComponent());
	CableComp1->SetupAttachment(SceneComponent);
	CableComp2->SetupAttachment(SceneComponent);
	CableComp3->SetupAttachment(SceneComponent);
	CableComp4->SetupAttachment(SceneComponent);

	CableNiagaraComp1->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CableNiagaraComp2->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CableNiagaraComp3->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CableNiagaraComp4->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	DeathNiagara->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	DieAudio->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ScreamAudio->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DamageAlarmAudio->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionAudio->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SoulLocation->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CableComponents.Add(CableComp1);
	CableComponents.Add(CableComp2);
	CableComponents.Add(CableComp3);
	CableComponents.Add(CableComp4);

	CableNiagaraComponents.Add(CableNiagaraComp1);
	CableNiagaraComponents.Add(CableNiagaraComp2);
	CableNiagaraComponents.Add(CableNiagaraComp3);
	CableNiagaraComponents.Add(CableNiagaraComp4);
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

void AEnemyCharacter::SetDieState() {
	ACorneredCharacter::SetDieState();

	DieAudio->Play();

	for (int i = 0; i < CableComponents.Num(); i++) {

		CableComponents[i]->bAttachStart = false;
		CableComponents[i]->bAttachEnd = false;
	}

	PlayDieNiagara();
}

void AEnemyCharacter::PlayDieNiagara() {

	FName BoneName = TEXT("NeckBottom");

	// Reattach Niagara component to the skeletal mesh (ragdoll)
	DeathNiagara->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		BoneName
	);

	// Optionally, reset transform after attaching
	DeathNiagara->SetRelativeLocation(FVector::ZeroVector);
	DeathNiagara->SetRelativeRotation(FRotator::ZeroRotator);

	FTimerManager& TimerManager = GetWorldTimerManager();

	TimerManager.SetTimer(TimerHandle1, this, &AEnemyCharacter::PlayExplosion1, FMath::RandRange(0.f,2.f), false);
	TimerManager.SetTimer(TimerHandle2, this, &AEnemyCharacter::PlayExplosion1, FMath::RandRange(0.f, 2.f), false);
	TimerManager.SetTimer(TimerHandle3, this, &AEnemyCharacter::PlayExplosion1, FMath::RandRange(0.f, 2.f), false);
	TimerManager.SetTimer(TimerHandle4, this, &AEnemyCharacter::PlayExplosion1, FMath::RandRange(0.f, 2.f), false);
}

void AEnemyCharacter::PlayExplosion1() {
	DeathNiagara->Activate();
	ExplosionAudio->Play();
}

void AEnemyCharacter::PlayExplosion2() {
	PlayCableNiagara(1);
	ExplosionAudio->Play();
}

void AEnemyCharacter::PlayExplosion3() {
	PlayCableNiagara(2);
	ExplosionAudio->Play();
}

void AEnemyCharacter::PlayExplosion4() {
	PlayCableNiagara(3);
	ExplosionAudio->Play();
}

void AEnemyCharacter::AttachEndpointOfCable(int index, UMaterialInterface* Material, bool shouldAttach) {

	if (index < 0 || index >= CableComponents.Num()) {
		return;
	}

	if (Material) {
		CableComponents[index]->SetMaterial(0, Material);
	}

	CableComponents[index]->bAttachEnd = shouldAttach;
}

void AEnemyCharacter::PlayDamageSounds() {
	ScreamAudio->Play();
	DamageAlarmAudio->Play();
	ExplosionAudio->Play();
}

void AEnemyCharacter::PlayCableNiagara(int index) {
	CableNiagaraComponents[index]->Activate();
}

int AEnemyCharacter::GetCountOfCable() {
	return CableComponents.Num();
}

FVector AEnemyCharacter::GetSoulLocation() {
	return GetMesh()->GetComponentLocation();
}