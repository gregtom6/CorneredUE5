// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Soul.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class UNiagaraComponent;
class UStaticMeshComponent;
class UConfig_Soul;
class ASoulRoute;
class USplineComponent;
class UAudioComponent;

UENUM(BlueprintType)
enum class ESoulMoveState : uint8 {
	Appear,
	MoveUpwards,
	MoveTowardsSpline,
	MovingTowardsSpline,
	MoveAlongSpline,
	MoveTowardsCollector,
	Disappear,

	Count,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoulDestroyedDelegate);

UCLASS()
class CORNERED_API ASoul : public AActor
{
	GENERATED_BODY()

public:

	FSoulDestroyedDelegate OnSoulDestroyed;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Movable;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> UpMoveTarget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Skull;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> LegNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> StartNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> EndNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> SoulAudio;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BadSignMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Soul> SoulConfig;

	ESoulMoveState MoveState;

	FVector StartingPosition;
	FVector TargetPosition;

	float ToSplineProgress = 0.f;

	ASoulRoute* SoulRoute;
	
public:	
	// Sets default values for this actor's properties
	ASoul();

	void SetSoulRoute(ASoulRoute* SoulRoute);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
