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

UCLASS()
class CORNERED_API ASoul : public AActor
{
	GENERATED_BODY()

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
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> LegNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> StartNiagara;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> EndNiagara;

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
