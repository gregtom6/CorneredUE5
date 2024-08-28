// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CorneredCharacter.h"
#include "PlayerCharacter.generated.h"

class UInteractableDetector;
class UPicker;
class UEquipper;
class UInteractor;
class UAudioComponent;
class UCharacterAnimInstance;

UCLASS()
class CORNERED_API APlayerCharacter : public ACorneredCharacter
{
	GENERATED_BODY()
public:
	// Called every frame


	UPROPERTY(EditAnywhere)
		TObjectPtr<UInteractableDetector> InteractableDetectorComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UPicker> PickerComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UEquipper> EquipperComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInteractor> InteractorComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UAudioComponent> EquipAudio;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:

	virtual IMovableCharacter* GetOwnedController() const override;

	virtual UCharacterAnimInstance* GetOwnedAnimInstance() const override;
};
