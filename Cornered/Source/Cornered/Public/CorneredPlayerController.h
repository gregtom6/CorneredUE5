// Fill out your copyright notice in the Description page of Project Settings.

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
	UInputAction* ActionInteract;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
	UInputAction* ActionPickup;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
	UInputAction* ActionDrop;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input|Character Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere)
		UConfig_Character_General* ConfigCharacter;

protected:

	virtual void OnPossess(APawn*) override;
	virtual void OnUnPossess() override;

	void HandleMovement(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleInteract();
	void HandlePickup();
	void HandleDrop();

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;

};
