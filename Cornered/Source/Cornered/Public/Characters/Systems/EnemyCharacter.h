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
class USceneComponent;

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

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> ScreamAudio;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> DamageAlarmAudio;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> ExplosionAudio;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UExternalEquipper> ExternalEquipperComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPawnSensingComponent> PawnSensingComp;

	UPROPERTY()
	TArray<TObjectPtr<UCableComponent>> CableComponents;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> CableNiagaraComp1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp2;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> CableNiagaraComp2;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp3;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> CableNiagaraComp3;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCableComponent> CableComp4;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> CableNiagaraComp4;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> DeathNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> FallenParticlesNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SoulLocation;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UNiagaraComponent>> CableNiagaraComponents;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_AI> AIConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_DamageVisual> DamageVisualConfig;

	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	FTimerHandle TimerHandle3;
	FTimerHandle TimerHandle4;


public:
	AEnemyCharacter();

	void SetEquipment(FItemData weapon, FItemData shield, FItemData additional);

	virtual void SetDieState() override;

	void AttachEndpointOfCable(int32 index, UMaterialInterface* Material, bool shouldAttach);

	void PlayDamageSounds();

	void PlayFallenParticles();

	void PlayCableNiagara(int32 index);

	int32 GetCountOfCable();

	FVector GetSoulLocation();

protected:

	virtual void BeginPlay() override;

	virtual IMovableCharacter* GetOwnedController() const override;

	virtual UCharacterAnimInstance* GetOwnedAnimInstance() const override;

	virtual bool IsSeeingInteractable() const override;

private:
	void PlayExplosion1();
	void PlayExplosion2();
	void PlayExplosion3();
	void PlayExplosion4();

	void PlayDieNiagara();
};
