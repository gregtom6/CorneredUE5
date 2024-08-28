// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Walls/EquipmentHint.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "Configs/DataAssets/Config_Hint.h"
#include "Characters/Systems/EquipmentDecider.h"

AEquipmentHint::AEquipmentHint()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ShieldMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComp"));
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComp"));

	SetRootComponent(Root);
	ShieldMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	WeaponMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEquipmentHint::BeginPlay()
{
	Super::BeginPlay();
	
	UEquipmentDecider* MySubsystem = GetWorld()->GetSubsystem<UEquipmentDecider>();
	if (MySubsystem)
	{
		MySubsystem->OnEquipmentDecided.AddDynamic(this, &AEquipmentHint::OnEquipmentDecided);
	}
}

void AEquipmentHint::OnEquipmentDecided(FItemDatas Weapon, FItemDatas Shield, FItemDatas Additional) {
	WeaponMeshComp->SetMaterial(0, HintConfig->GetMaterialBasedOnItemType(Weapon.Key));
	ShieldMeshComp->SetMaterial(0, HintConfig->GetMaterialBasedOnItemType(Shield.Key));
}
