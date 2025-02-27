// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "PlayerCharacter.generated.h"

class UInteractableDetector;
class UPicker;
class UEquipper;
class UInteractor;
class UAudioComponent;
class UCharacterAnimInstance;
class UPostProcessController;
class UConfig_Time;
class UConfig_Character_General;

UCLASS()
class CORNERED_API APlayerCharacter : public ACorneredCharacter
{
	GENERATED_BODY()

private:
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

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> DeathAudio;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPostProcessController> PostProcessController;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Time> TimeConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Character_General> CharacterConfig;

	bool bCharacterDied;

	float TimeWhenDamageHappened;

	bool bCharacterReceivedShot;

	float SelectedRotation;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual IMovableCharacter* GetOwnedController() const override;

	virtual UCharacterAnimInstance* GetOwnedAnimInstance() const override;

	virtual bool IsSeeingInteractable() const override;

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);

	UFUNCTION()
	void OnCharacterShotReceived(ACorneredCharacter* DefeatedCharacter);

	void ProcessDeathAudio();

	void ProcessShotReceivingCamera();
};
