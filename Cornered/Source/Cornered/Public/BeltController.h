// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Config_Belt.h"
#include "BeltController.generated.h"

class UBoxComponent;
class UConfig_Belt;
class ACorneredObjectPool;
class ACorneredButton;

UCLASS()
class CORNERED_API ABeltController : public AActor
{
	GENERATED_BODY()

public:
	ABeltController();

protected:
	virtual void BeginPlay() override;

public:

	UFUNCTION()
		float GetCurrentMultiplier();

	UFUNCTION()
		EBeltSpeed GetCurrentBeltSpeed();

private:

	UFUNCTION()
		void PressHappened();

	UFUNCTION()
		void SwitchBeltSpeed();

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UBoxComponent> SpawnPointComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UBoxComponent> DespawnPointComp;


	UPROPERTY()
		EBeltSpeed CurrentBeltSpeed;

	UPROPERTY(EditAnywhere)
		UConfig_Belt* BeltConfig;

	UPROPERTY(EditAnywhere)
		TObjectPtr<ACorneredObjectPool> ObjectPool;

	UFUNCTION()
		void ObjectPoolInitialized();

	UPROPERTY(EditAnywhere)
		TObjectPtr<ACorneredButton> CorneredButton;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
