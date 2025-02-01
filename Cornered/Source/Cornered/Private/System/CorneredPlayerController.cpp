// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Configs/DataAssets/Config_Character_General.h"
#include "System/CorneredCheats.h"

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

	//UCorneredCheats* CorneredCheats = Cast<UCorneredCheats>(CheatManager);

	//if (CorneredCheats) {
		//CorneredCheats->RegisterCommands();
	//}
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
		MovingCameraPitch(CameraComponent, CameraRotation, LookAxisVector.Y);
	}
}

void ACorneredPlayerController::HandleLookUp() {

	HandleVerticalLook(1.f);
}

void ACorneredPlayerController::HandleLookDown() {

	HandleVerticalLook(-1.0f);
}

void ACorneredPlayerController::HandleVerticalLook(float Multiplier) {
	UCameraComponent* CameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
	if (CameraComponent) {
		FRotator CameraRotation = CameraComponent->GetComponentRotation();
		MovingCameraPitch(CameraComponent, CameraRotation, Multiplier * ConfigCharacter->LookVerticalSensitivity);
	}
}

void ACorneredPlayerController::MovingCameraPitch(UCameraComponent* CameraComponent,FRotator Rotator, float Delta) {
	if (ConfigCharacter->HeadMinRotY < Rotator.Pitch + Delta && Rotator.Pitch + Delta < ConfigCharacter->HeadMaxRotY) {
		Rotator.Pitch += Delta;

		CameraComponent->SetWorldRotation(Rotator);
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