// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/SoulSniffer.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/Systems/CharacterSpawner.h"

// Sets default values
ASoulSniffer::ASoulSniffer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Target= CreateDefaultSubobject<USceneComponent>(TEXT("Target"));

	SetRootComponent(Root);
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Target->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASoulSniffer::BeginPlay()
{
	Super::BeginPlay();
	
	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->SetSoulSniffer(this);
	}
}

// Called every frame
void ASoulSniffer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASoulSniffer::GetTargetLocation() {
	return Target->GetComponentLocation();
}