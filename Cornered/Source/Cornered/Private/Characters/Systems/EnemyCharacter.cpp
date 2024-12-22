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
	LeftRepairArmNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LeftRepairArmNiagara"));
	RightRepairArmNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RightRepairArmNiagara"));
	CableComp1 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon1"));
	CableComp2 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon2"));
	CableComp3 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon3"));
	CableComp4 = CreateDefaultSubobject<UCableComponent>(TEXT("CableCompon4"));

	USceneComponent* SceneComponent = Cast<USceneComponent>(GetCapsuleComponent());
	CableComp1->SetupAttachment(SceneComponent);
	CableComp2->SetupAttachment(SceneComponent);
	CableComp3->SetupAttachment(SceneComponent);
	CableComp4->SetupAttachment(SceneComponent);

	
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CableComponents.Add(CableComp1);
	CableComponents.Add(CableComp2);
	CableComponents.Add(CableComp3);
	CableComponents.Add(CableComp4);
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

int AEnemyCharacter::GetCountOfCable() {
	return CableComponents.Num();
}