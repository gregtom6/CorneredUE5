// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MovableCharacter.h"
#include "CorneredPlayerController.generated.h"

class UEnhancedInputComponent;
class APlayerCharacter;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UCameraComponent;
class UConfig_Character_General;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickupInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDropInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShootInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractStartedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractHappenedDelegate);

UCLASS(Abstract)
class CORNERED_API ACorneredPlayerController : public APlayerController, public IMovableCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionLook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionLookUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionLookDown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionLookLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionLookRight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionInteract;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionPickup;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionDrop;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionEquip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputAction> ActionShoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Character_General> ConfigCharacter;

	FPickupInteractionHappenedDelegate PickupHappenedInstance;

	FDropInteractionHappenedDelegate DropHappenedInstance;

	FEquipInteractionHappenedDelegate EquipHappenedInstance;

	FShootInteractionHappenedDelegate ShootHappenedInstance;

	FInteractStartedDelegate InteractStartedInstance;

	FInteractHappenedDelegate InteractHappenedInstance;

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;

	EMovementState MovementState;

public:
	UFUNCTION(BlueprintPure)
		virtual EMovementState GetMovementState() const override;

protected:

	virtual void OnPossess(APawn*) override;
	virtual void OnUnPossess() override;

	UFUNCTION()
		void HandleMovement(const FInputActionValue& InputActionValue);
	UFUNCTION()
		void MovementCompleted(const FInputActionValue& InputActionValue);
	UFUNCTION()
		void HandleLook(const FInputActionValue& InputActionValue);
	UFUNCTION()
		void HandleLookUp();
	UFUNCTION()
		void HandleLookDown();
	UFUNCTION()
		void HandleLookLeft();
	UFUNCTION()
		void HandleLookRight();
	UFUNCTION()
		void HandleInteractStarted();
	UFUNCTION()
		void HandleInteractFinished();
	UFUNCTION()
		void HandlePickup();
	UFUNCTION()
		void HandleDrop();
	UFUNCTION()
		void HandleEquip();
	UFUNCTION()
		void HandleShoot();
};
