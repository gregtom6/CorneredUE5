// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Walls/EquipmentHint.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "Configs/DataAssets/Config_Hint.h"
#include "Characters/Systems/EquipmentDecider.h"
#include "Components/RectLightComponent.h"
#include "Environment/Others/LightBlinkController.h"
#include "Materials/MaterialInstanceDynamic.h"

AEquipmentHint::AEquipmentHint()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ShieldMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMeshComp"));
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComp"));
	LightMeshWeapon= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMeshWeapon"));
	LightMeshShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMeshShield"));
	RectLightWeapon = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightWeapon"));
	RectLightShield = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightShield"));
	LightBlinkController = CreateDefaultSubobject<ULightBlinkController>(TEXT("LightBlinkController"));

	SetRootComponent(Root);
	ShieldMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	WeaponMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	RectLightWeapon->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	RectLightShield->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	LightMeshWeapon->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	LightMeshShield->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEquipmentHint::BeginPlay()
{
	Super::BeginPlay();
	
	UEquipmentDecider* MySubsystem = GetWorld()->GetSubsystem<UEquipmentDecider>();
	if (MySubsystem)
	{
		MySubsystem->OnEquipmentDecided.AddUniqueDynamic(this, &AEquipmentHint::OnEquipmentDecided);
	}
}

void AEquipmentHint::OnEquipmentDecided(FItemDatas Weapon, FItemDatas Shield, FItemDatas Additional) {
	WeaponMeshComp->SetMaterial(0, HintConfig->GetMaterialBasedOnItemType(Weapon.Key));
	ShieldMeshComp->SetMaterial(0, HintConfig->GetMaterialBasedOnItemType(Shield.Key));
}

TArray<ULightComponent*> AEquipmentHint::GetLightComponents()
{
	TArray<ULightComponent*> Lights;
	Lights.Add(RectLightWeapon);
	Lights.Add(RectLightShield);
	return Lights;
}

TArray<UMaterialInstanceDynamic*> AEquipmentHint::GetLightMaterials()
{
	TArray<UMaterialInstanceDynamic*> Materials;
	Materials.Add(LightMeshWeapon->CreateAndSetMaterialInstanceDynamic(0));
	Materials.Add(LightMeshShield->CreateAndSetMaterialInstanceDynamic(0));
	return Materials;
}
