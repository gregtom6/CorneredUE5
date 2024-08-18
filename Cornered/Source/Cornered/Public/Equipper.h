// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Equipper.generated.h"

class UPicker;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UEquipper : public USceneComponent
{
	GENERATED_BODY()

public:	
	UEquipper();

	UPROPERTY()
		TObjectPtr<UPicker> PickerComp;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void EquipHappened();
};
