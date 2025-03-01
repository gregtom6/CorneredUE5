// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquippedWeapon.generated.h"

class USceneComponent;
class UPointLightComponent;
class UActorSequenceComponent;
class UActorSequencePlayer;
class UNiagaraComponent;
class UAudioComponent;
class UConfig_Equipment;

USTRUCT(BlueprintType)
struct FShotRayDatas
{
	FShotRayDatas()
		: Origin(0.f, 0.f, 0.f), End(0.f, 0.f, 0.f) { }


	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	FVector Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	FVector End;

};

UCLASS()
class CORNERED_API AEquippedWeapon : public AActor
{
	GENERATED_BODY()

private:

	static const FName BeamStart;
	static const FName BeamEnd;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> ShotSequ;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPointLightComponent> PointLightComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> MuzzlePosition;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> ShootRaycastStartPosition;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> SmokeComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> MuzzleFlashComp;

	UPROPERTY()
	TObjectPtr<AActor> EquipperActor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> ShotAudio;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Equipment> EquipmentConfig;

public:
	AEquippedWeapon();
	void ShotHappened();

	void SetEquipperActor(AActor* equipper);

	FShotRayDatas GetShotRayDatas() const;

protected:
	virtual void BeginPlay() override;
};
