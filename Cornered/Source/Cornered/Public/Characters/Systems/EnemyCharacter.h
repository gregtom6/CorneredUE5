// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "Configs/DataAssets/Config_Equipment.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;
class AEnemyController;
class AController;
class UExternalEquipper;
class UStateTreeComponent;
class UConfig_AI;
class UHideSpotFinder;
class UCharacterAnimInstance;
class UInteractableDetector;
class UAudioComponent;
class UCableComponent;
class UNiagaraComponent;
class UMaterialInterface;
class UConfig_DamageVisual;

UCLASS()
class CORNERED_API AEnemyCharacter : public ACorneredCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStateTreeComponent> StateTreeComp;

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UHideSpotFinder> HideSpotFinderComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> DieAudio;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UExternalEquipper> ExternalEquipperComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnSensingComponent> PawnSensingComp;

	TArray<UCableComponent*> CableComponents;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp2;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp3;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp4;

	UPROPERTY(VisibleAnywhere)
	TArray<UNiagaraComponent*> CableNiagaraComponents;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> LeftRepairArmNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> RightRepairArmNiagara;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_AI> AIConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_DamageVisual> DamageVisualConfig;

public:
	AEnemyCharacter();

	void SetEquipment(FItemDatas weapon, FItemDatas shield, FItemDatas additional);

	virtual void SetDieState() override;

	void AttachEndpointOfCable(int index, UMaterialInterface* Material, bool shouldAttach);

	int GetCountOfCable();

protected:

	//virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

	virtual IMovableCharacter* GetOwnedController() const override;

	virtual UCharacterAnimInstance* GetOwnedAnimInstance() const override;
};
