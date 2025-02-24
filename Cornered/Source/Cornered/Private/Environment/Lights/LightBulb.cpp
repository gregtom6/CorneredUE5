// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Lights/LightBulb.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"

ALightBulb::ALightBulb() {
	PointLightComp->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
}