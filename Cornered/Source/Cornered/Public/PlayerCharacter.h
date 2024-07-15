// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UPlayerWeapon;
class UInteractableDetector;
class UPicker;
class UEquipper;
class UCameraComponent;
class USkeletalMeshComponent;
class UEquipmentVisualizer;
class UInventory;
class UPaperSpriteComponent;
class UCooldownIndicator;
class UInteractor;
class UAudioComponent;

UCLASS()
class CORNERED_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPlayerWeapon> PlayerWeaponComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInteractableDetector> InteractableDetectorComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UPicker> PickerComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UEquipper> EquipperComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInteractor> InteractorComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UEquipmentVisualizer> EquipmentVisualizer;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInventory> InventoryComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> CooldownIndicatorParentComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPaperSpriteComponent> PaperSpriteComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPaperSpriteComponent> CooldownIndicatorComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UCooldownIndicator> CooldownIndicatorManagementComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UAudioComponent> EquipAudio;
};
