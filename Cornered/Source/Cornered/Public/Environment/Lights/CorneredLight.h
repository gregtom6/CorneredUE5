// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Environment/Lights/LightBlinkable.h"
#include "CorneredLight.generated.h"

class USpotLightComponent;
class UPointLightComponent;
class URectLightComponent;
class UStaticMeshComponent;

UCLASS()
class CORNERED_API ACorneredLight : public AActor, public ILightBlinkable
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpotLightComponent> SpotLightComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPointLightComponent> PointLightComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URectLightComponent> RectLightComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

public:	
	ACorneredLight();

	// Inherited via ILightBlinkable
	TArray<ULightComponent*> GetLightComponents() override;

	TArray<UMaterialInstanceDynamic*> GetLightMaterials() override;

};
