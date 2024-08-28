// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CorneredPlayerController.h"
#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Config_Character_General.h"

void ACorneredPlayerController::OnPossess(APawn* aPawn) {
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<APlayerCharacter>(aPawn);

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	SetInputMode(FInputModeGameOnly());

	//TODO: checkf for these two

	if (ActionMovement) {
		EnhancedInputComponent->BindAction(ActionMovement, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleMovement);
		EnhancedInputComponent->BindAction(ActionMovement, ETriggerEvent::Completed, this, &ACorneredPlayerController::MovementCompleted);
	}

	if (ActionLook) {
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleLook);
	}

	if (ActionLookUp) {
		EnhancedInputComponent->BindAction(ActionLookUp, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleLookUp);
	}
	if (ActionLookDown) {
		EnhancedInputComponent->BindAction(ActionLookDown, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleLookDown);
	}
	if (ActionLookLeft) {
		EnhancedInputComponent->BindAction(ActionLookLeft, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleLookLeft);
	}
	if (ActionLookRight) {
		EnhancedInputComponent->BindAction(ActionLookRight, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleLookRight);
	}

	if (ActionInteract) {
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Started, this, &ACorneredPlayerController::HandleInteractStarted);
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Completed, this, &ACorneredPlayerController::HandleInteractFinished);
	}

	if (ActionPickup) {
		EnhancedInputComponent->BindAction(ActionPickup, ETriggerEvent::Completed, this, &ACorneredPlayerController::HandlePickup);
	}

	if (ActionDrop) {
		EnhancedInputComponent->BindAction(ActionDrop, ETriggerEvent::Completed, this, &ACorneredPlayerController::HandleDrop);
	}

	if (ActionEquip) {
		EnhancedInputComponent->BindAction(ActionEquip, ETriggerEvent::Completed, this, &ACorneredPlayerController::HandleEquip);
	}

	if (ActionShoot) {
		EnhancedInputComponent->BindAction(ActionShoot, ETriggerEvent::Completed, this, &ACorneredPlayerController::HandleShoot);
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);
}

void ACorneredPlayerController::OnUnPossess() {
	Super::OnUnPossess();

	EnhancedInputComponent->ClearActionBindings();
}

void ACorneredPlayerController::HandleInteractStarted() {
	InteractStartedInstance.Broadcast();
}

void ACorneredPlayerController::HandleInteractFinished() {
	InteractHappenedInstance.Broadcast();
}

void ACorneredPlayerController::HandlePickup() {
	PickupHappenedInstance.Broadcast();
}

void ACorneredPlayerController::HandleDrop() {
	DropHappenedInstance.Broadcast();
}

void ACorneredPlayerController::HandleEquip() {
	EquipHappenedInstance.Broadcast();
}

void ACorneredPlayerController::HandleShoot() {
	ShootHappenedInstance.Broadcast();
}

void ACorneredPlayerController::HandleLook(const FInputActionValue& InputActionValue) {

	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);

	UCameraComponent* CameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	if (CameraComponent) {
		FRotator CameraRotation = CameraComponent->GetComponentRotation();
		if (ConfigCharacter->HeadMinRotY < CameraRotation.Pitch + LookAxisVector.Y && CameraRotation.Pitch + LookAxisVector.Y < ConfigCharacter->HeadMaxRotY) {
			CameraRotation.Pitch += LookAxisVector.Y;

			CameraComponent->SetWorldRotation(CameraRotation);
		}
	}
}

void ACorneredPlayerController::HandleLookUp() {
	UCameraComponent* CameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	if (CameraComponent) {
		FRotator CameraRotation = CameraComponent->GetComponentRotation();
		if (ConfigCharacter->HeadMinRotY < CameraRotation.Pitch + ConfigCharacter->LookVerticalSensitivity && CameraRotation.Pitch + ConfigCharacter->LookVerticalSensitivity < ConfigCharacter->HeadMaxRotY) {
			CameraRotation.Pitch += ConfigCharacter->LookVerticalSensitivity;

			CameraComponent->SetWorldRotation(CameraRotation);
		}
	}
}

void ACorneredPlayerController::HandleLookDown() {

	UCameraComponent* CameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	if (CameraComponent) {
		FRotator CameraRotation = CameraComponent->GetComponentRotation();
		if (ConfigCharacter->HeadMinRotY < CameraRotation.Pitch - ConfigCharacter->LookVerticalSensitivity && CameraRotation.Pitch - ConfigCharacter->LookVerticalSensitivity < ConfigCharacter->HeadMaxRotY) {
			CameraRotation.Pitch += -ConfigCharacter->LookVerticalSensitivity;

			CameraComponent->SetWorldRotation(CameraRotation);
		}
	}
}

void ACorneredPlayerController::HandleLookLeft() {
	AddYawInput(-ConfigCharacter->LookHorizontalSensitivity);
}

void ACorneredPlayerController::HandleLookRight() {
	AddYawInput(ConfigCharacter->LookHorizontalSensitivity);
}

void ACorneredPlayerController::HandleMovement(const FInputActionValue& InputActionValue) {

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (PlayerCharacter) {
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.X * ConfigCharacter->MovementMultiplier);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), -MovementVector.Y * ConfigCharacter->MovementMultiplier);

		if (!FMath::IsNearlyZero(MovementVector.X)) {
			MovementState = EMovementState::Strafing;
		}
		else if (!FMath::IsNearlyZero(MovementVector.Y)) {
			MovementState = EMovementState::Walking;
		}
	}
}

void ACorneredPlayerController::MovementCompleted(const FInputActionValue& InputActionValue) {

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (PlayerCharacter) {
		if (FMath::IsNearlyZero(MovementVector.X) && FMath::IsNearlyZero(MovementVector.Y)) {
			MovementState = EMovementState::Standing;
		}
	}
}

EMovementState ACorneredPlayerController::GetMovementState() const {
	return MovementState;
}