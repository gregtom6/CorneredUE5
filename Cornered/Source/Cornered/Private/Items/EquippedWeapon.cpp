// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Items/EquippedWeapon.h"
#include "Components/SceneComponent.h"
#include "Components/PointLightComponent.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <Camera/CameraComponent.h>
#include "Components/AudioComponent.h"
#include "Configs/DataAssets/Config_Equipment.h"

const FName AEquippedWeapon::BeamStart(TEXT("BeamStart"));
const FName AEquippedWeapon::BeamEnd(TEXT("BeamEnd"));

AEquippedWeapon::AEquippedWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePosition"));
	ShootRaycastStartPosition= CreateDefaultSubobject<USceneComponent>(TEXT("ShootRaycastStartPosition"));
	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	MuzzleFlashComp= CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlashComp"));
	SmokeComp= CreateDefaultSubobject<UNiagaraComponent>(TEXT("SmokeComp"));
	ShotAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotAudio"));

	SetRootComponent(Root);
	MuzzlePosition->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ShootRaycastStartPosition->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	PointLightComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	MuzzleFlashComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	SmokeComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ShotAudio->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEquippedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	PointLightComp->SetIntensity(0.f);
}

void AEquippedWeapon::ShotHappened() {

	if (ShotSequ) {
		ShotSequ->StopSequence();
		ShotSequ->PlaySequence();

		FShotRayDatas ShotDatas = GetShotRayDatas();

		NiagaraComp->SetVariablePosition(BeamStart, MuzzlePosition->GetComponentLocation());
		NiagaraComp->SetVariablePosition(BeamEnd, ShotDatas.End);

		NiagaraComp->Activate(true);

		MuzzleFlashComp->Activate(true);

		SmokeComp->Activate(true);
	}

	ShotAudio->Play();
}

void AEquippedWeapon::SetEquipperActor(AActor* equipper) {
	EquipperActor = equipper;
}

FShotRayDatas AEquippedWeapon::GetShotRayDatas() const {

	if (!EquipperActor) {
		return FShotRayDatas();
	}

	FShotRayDatas ShotDatas;

	UCameraComponent* cameraComp = EquipperActor->FindComponentByClass<UCameraComponent>();

	ShotDatas.Origin = ShootRaycastStartPosition->GetComponentLocation();
	ShotDatas.End = cameraComp->GetComponentLocation() + (cameraComp->GetForwardVector() * EquipmentConfig->ShotRayDistance);

	return ShotDatas;
}