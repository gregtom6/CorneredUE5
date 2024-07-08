// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippedWeapon.h"
#include "Components/SceneComponent.h"
#include "Components/PointLightComponent.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"

// Sets default values
AEquippedWeapon::AEquippedWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(Root);

	MuzzlePosition = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzlePosition"));

	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));

	MuzzlePosition->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	PointLightComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEquippedWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	PointLightComp->Intensity = 0.f;
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
		player->Play();
	}
}