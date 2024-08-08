// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EquipmentHint.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Config_Equipment.h"
#include "Config_Hint.h"
#include "EquipmentDecider.h"

// Sets default values
AEquipmentHint::AEquipmentHint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ShieldMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComp"));

	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComp"));

	SetRootComponent(Root);

	ShieldMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	WeaponMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEquipmentHint::BeginPlay()
{
	Super::BeginPlay();
	
	UEquipmentDecider* MySubsystem = GetWorld()->GetSubsystem<UEquipmentDecider>();
	if (MySubsystem)
	{
		MySubsystem->OnEquipmentDecided.AddDynamic(this, &AEquipmentHint::OnEquipmentDecided);
	}
	
}

// Called every frame
void AEquipmentHint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipmentHint::OnEquipmentDecided(FItemDatas Weapon, FItemDatas Shield, FItemDatas Additional) {
	WeaponMeshComp->SetMaterial(0, HintConfig->GetMaterialBasedOnItemType(Weapon.Key));
	ShieldMeshComp->SetMaterial(0, HintConfig->GetMaterialBasedOnItemType(Shield.Key));
}
