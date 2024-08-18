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

USTRUCT(BlueprintType)
struct FShotRayDatas
{
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
	
public:	
	AEquippedWeapon();

protected:
	virtual void BeginPlay() override;

public:	

	UPROPERTY()
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> MuzzlePosition;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPointLightComponent> PointLightComp;
	UPROPERTY()
		UActorSequenceComponent* ShotSequ;

	UFUNCTION()
		void ShotHappened();

	UFUNCTION()
		void SetEquipperActor(AActor* equipper);

	UFUNCTION()
		FShotRayDatas GetShotRayDatas();
	
private:

	UPROPERTY(VisibleAnywhere)
		UNiagaraComponent* NiagaraComp;
		
	UPROPERTY()
		TObjectPtr<AActor> EquipperActor;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> ShotAudio;
};
