// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/Systems/MovableCharacter.h"
#include "CorneredCharacter.generated.h"

class UCharacterWeapon;
class UCameraComponent;
class UEquipmentVisualizer;
class UInventory;
class UPaperSpriteComponent;
class UCooldownIndicator;
class UCharacterHealth;
class UCharacterAnimInstance;

UCLASS()
class CORNERED_API ACorneredCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCharacterWeapon> CharacterWeaponComp;

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
	TObjectPtr<UCharacterHealth> CharacterHealthComp;

public:
	// Sets default values for this character's properties
	ACorneredCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual IMovableCharacter* GetOwnedController() const PURE_VIRTUAL(ACorneredCharacter::GetOwnedController, return nullptr;);

	virtual UCharacterAnimInstance* GetOwnedAnimInstance() const PURE_VIRTUAL(ACorneredCharacter::GetOwnedAnimInstance, return nullptr;);
};
