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


// Sets default values
AEquippedWeapon::AEquippedWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called when the game starts or when spawned
void AEquippedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	PointLightComp->SetIntensity(0.f);
}

// Called every frame
void AEquippedWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

		UCameraComponent* cameraComp = Cast<UCameraComponent>(EquipperActor->GetComponentByClass(UCameraComponent::StaticClass()));

		NiagaraComp->SetVariablePosition("BeamStart", MuzzlePosition->GetComponentLocation());
		NiagaraComp->SetVariablePosition("BeamEnd", cameraComp->GetComponentLocation() + (cameraComp->GetForwardVector() * 10000.0f));

		NiagaraComp->Activate(true);
	}

	ShotAudio->Play();
}

void AEquippedWeapon::SetEquipperActor(AActor* equipper) {
	EquipperActor = equipper;
}