// Fill out your copyright notice in the Description page of Project Settings.


#include "CorneredPlayerController.h"
#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"

void ACorneredPlayerController::OnPossess(APawn* aPawn) {
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<APlayerCharacter>(aPawn);

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	//TODO: checkf for these two

	if (ActionMovement) {
		EnhancedInputComponent->BindAction(ActionMovement, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleMovement);
	}

	if (ActionLook) {
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleLook);
	}

	if (ActionInteract) {
		EnhancedInputComponent->BindAction(ActionInteract, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleInteract);
	}

	if (ActionPickup) {
		EnhancedInputComponent->BindAction(ActionPickup, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandlePickup);
	}

	if (ActionDrop) {
		EnhancedInputComponent->BindAction(ActionDrop, ETriggerEvent::Triggered, this, &ACorneredPlayerController::HandleDrop);
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);
}

void ACorneredPlayerController::OnUnPossess() {
	Super::OnUnPossess();

	EnhancedInputComponent->ClearActionBindings();
}

void ACorneredPlayerController::HandleInteract() {

}

void ACorneredPlayerController::HandlePickup() {

}

void ACorneredPlayerController::HandleDrop() {

}

void ACorneredPlayerController::HandleLook(const FInputActionValue& InputActionValue) {

	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ACorneredPlayerController::HandleMovement(const FInputActionValue& InputActionValue) {

	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (PlayerCharacter) {
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.X);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), -MovementVector.Y);
	}
}