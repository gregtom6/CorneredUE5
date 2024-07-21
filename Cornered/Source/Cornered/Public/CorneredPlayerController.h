// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CorneredPlayerController.generated.h"

class UEnhancedInputComponent;
class APlayerCharacter;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UCameraComponent;
class UConfig_Character_General;

UENUM(BlueprintType)
enum class EMovementState : uint8 {
	Standing,
	Walking,
	Strafing,

	Count,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickupInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDropInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShootInteractionHappenedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractStartedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractHappenedDelegate);

/**
 *
 */
UCLASS(Abstract)
class CORNERED_API ACorneredPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionLook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionLookUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionLookDown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionLookLeft;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionLookRight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionInteract;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionPickup;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionDrop;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionEquip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		UInputAction* ActionShoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
		TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere)
		UConfig_Character_General* ConfigCharacter;

	UFUNCTION()
		EMovementState GetMovementState() const;

protected:

	virtual void OnPossess(APawn*) override;
	virtual void OnUnPossess() override;

	void HandleMovement(const FInputActionValue& InputActionValue);
	void MovementCompleted(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleLookUp();
	void HandleLookDown();
	void HandleLookLeft();
	void HandleLookRight();
	void HandleInteractStarted();
	void HandleInteractFinished();
	void HandlePickup();
	void HandleDrop();
	void HandleEquip();
	void HandleShoot();

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;

	UPROPERTY()
		EMovementState MovementState;

public:

	UPROPERTY()
		FPickupInteractionHappenedDelegate PickupHappenedInstance;

	UPROPERTY()
		FDropInteractionHappenedDelegate DropHappenedInstance;

	UPROPERTY()
		FEquipInteractionHappenedDelegate EquipHappenedInstance;

	UPROPERTY()
		FShootInteractionHappenedDelegate ShootHappenedInstance;

	UPROPERTY()
		FInteractStartedDelegate InteractStartedInstance;

	UPROPERTY()
		FInteractHappenedDelegate InteractHappenedInstance;
};
