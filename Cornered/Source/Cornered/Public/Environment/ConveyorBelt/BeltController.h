// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Configs/DataAssets/Config_Belt.h"
#include "BeltController.generated.h"

class UBoxComponent;
class UConfig_Belt;
class ACorneredObjectPool;
class ACorneredButton;

UCLASS()
class CORNERED_API ABeltController : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<ACorneredButton> CorneredButton;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> SpawnPointComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> DespawnPointComp;

	EBeltSpeed CurrentBeltSpeed;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Belt> BeltConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ACorneredObjectPool> ObjectPool;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> CurrentlyVisibleBeltElements;

public:
	ABeltController();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	EBeltSpeed GetCurrentBeltSpeed() const;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintPure)
	float GetCurrentMultiplier() const;
	UFUNCTION()
	void PressHappened();

	UFUNCTION()
	void ObjectPoolInitialized();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SwitchBeltSpeed();

};
