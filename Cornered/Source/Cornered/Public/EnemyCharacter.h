// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Config_Equipment.h"
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
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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
		TObjectPtr<UConfig_AI> AIConfig;

		void SetEquipment(FItemDatas weapon, FItemDatas shield, FItemDatas additional);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
