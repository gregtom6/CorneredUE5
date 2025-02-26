// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Lights/CorneredLight.h"
#include "Components/RectLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACorneredLight::ACorneredLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SpotLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComp"));
	PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));
	RectLightComp = CreateDefaultSubobject<URectLightComponent>(TEXT("RectLightComp"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));

	SetRootComponent(Root);
	SpotLightComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	PointLightComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	RectLightComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

TArray<ULightComponent*> ACorneredLight::GetLightComponents()
{
	TArray<ULightComponent*> Lights;
	Lights.Add(SpotLightComp);
	Lights.Add(PointLightComp);
	Lights.Add(RectLightComp);
	return Lights;
}

TArray<UMaterialInstanceDynamic*> ACorneredLight::GetLightMaterials()
{
	TArray<UMaterialInstanceDynamic*> Materials;
	Materials.Add(StaticMeshComp->CreateAndSetMaterialInstanceDynamic(0));
	return Materials;
}

