// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CorneredButton.h"
#include "Materials/MaterialInterface.h"
#include "ConveyorBeltSpeederButton.generated.h"

class UStaticMeshComponent;
class UConfig_Belt;
class ABeltController;

UCLASS()
class CORNERED_API AConveyorBeltSpeederButton : public ACorneredButton
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStaticMeshComponent> BeltButtonStaticMeshComp;
	
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Belt> BeltConfig;

	UPROPERTY(EditAnywhere)
		TObjectPtr<ABeltController> BeltController;

public:

	AConveyorBeltSpeederButton();

	void Interact() override;

protected:

	virtual void BeginPlay() override;

};
