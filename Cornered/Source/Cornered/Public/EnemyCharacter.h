// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UEnemyWeapon;
class UCameraComponent;
class USkeletalMeshComponent;
class UEquipmentVisualizer;
class UInventory;
class UPaperSpriteComponent;
class UCooldownIndicator;
class UPawnSensingComponent;
class UEnemyHealth;
class AEnemyController;
class AGameModeBase;
class APlayerController;
class APawn;
class AAIController;
class UExternalEquipper;
class UStateTreeComponent;
class UConfig_AI;
class UHideSpotFinder;

UCLASS()
class CORNERED_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	APawn* ChasedTarget = nullptr;

	UFUNCTION()
		void Chase(APawn* targetPawn);
	/*
	UPROPERTY(BlueprintReadWrite, BlueprintGetter = GetLifeForAttack)
		float AttackWhenLifeMoreThanPercentage;

	UPROPERTY(BlueprintReadWrite, BlueprintGetter = GetLifeForHide)
		float HideWhenLifeLessThanPercentage;
		*/
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UEnemyWeapon> EnemyWeaponComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UEquipmentVisualizer> EquipmentVisualizer;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInventory> InventoryComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UHideSpotFinder> HideSpotFinderComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UExternalEquipper> ExternalEquipperComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> CooldownIndicatorParentComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPaperSpriteComponent> PaperSpriteComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPaperSpriteComponent> CooldownIndicatorComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UCooldownIndicator> CooldownIndicatorManagementComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPawnSensingComponent> PawnSensingComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UEnemyHealth> EnemyHealthComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStateTreeComponent> StateTreeComp;

	UPROPERTY(EditAnywhere)
		UConfig_AI* AIConfig;

	UFUNCTION()
		void SetEquipment(FItemDatas weapon, FItemDatas shield, FItemDatas additional);
	/*
	UFUNCTION(BlueprintGetter)
		float GetLifeForAttack();

	UFUNCTION(BlueprintGetter)
		float GetLifeForHide();
		*/

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
