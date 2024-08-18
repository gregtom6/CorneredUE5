// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EquippedWeapon.h"
#include "Components/SceneComponent.h"
#include "Components/PointLightComponent.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <Camera/CameraComponent.h>
#include "Components/AudioComponent.h"

AEquippedWeapon::AEquippedWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePosition"));

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));

	ShotAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotAudio"));

	MuzzlePosition->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	PointLightComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	NiagaraComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	ShotAudio->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEquippedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	PointLightComp->SetIntensity(0.f);
}

void AEquippedWeapon::ShotHappened() {

	TArray<UActorSequenceComponent*> ActorSequenceComponents;
	GetComponents<UActorSequenceComponent>(ActorSequenceComponents);

	for (int i = 0; i < ActorSequenceComponents.Num(); i++)
	{
		if (ActorSequenceComponents[i]->GetFName() == FName("ShotSequence"))
		{
			ShotSequ = ActorSequenceComponents[i];
			break;
		}
	}

	UActorSequencePlayer* player = ShotSequ->GetSequencePlayer();
	if (player) {
		player->Stop();
		player->Play();

		FShotRayDatas ShotDatas = GetShotRayDatas();

		NiagaraComp->SetVariablePosition("BeamStart", ShotDatas.Origin);
		NiagaraComp->SetVariablePosition("BeamEnd", ShotDatas.End);

		NiagaraComp->Activate(true);
	}

	ShotAudio->Play();
}

void AEquippedWeapon::SetEquipperActor(AActor* equipper) {
	EquipperActor = equipper;
}

FShotRayDatas AEquippedWeapon::GetShotRayDatas() {
	FShotRayDatas ShotDatas;

	UCameraComponent* cameraComp = Cast<UCameraComponent>(EquipperActor->GetComponentByClass(UCameraComponent::StaticClass()));

	ShotDatas.Origin = MuzzlePosition->GetComponentLocation();
	ShotDatas.End = cameraComp->GetComponentLocation() + (cameraComp->GetForwardVector() * 10000.0f);

	return ShotDatas;
}