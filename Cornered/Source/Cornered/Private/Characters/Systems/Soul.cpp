// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/Systems/Soul.h"
#include "NiagaraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Configs/DataAssets/Config_Soul.h"
#include "Environment/Others/SoulRoute.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ASoul::ASoul()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Movable = CreateDefaultSubobject<USceneComponent>(TEXT("Movable"));
	UpMoveTarget = CreateDefaultSubobject<USceneComponent>(TEXT("UpMoveTarget"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	LegNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LegNiagara"));
	StartNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("StartNiagara"));
	EndNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EndNiagara"));
	Skull = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skull"));

	SetRootComponent(Root);
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Movable->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	UpMoveTarget->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Skull->AttachToComponent(Movable, FAttachmentTransformRules::KeepRelativeTransform);
	LegNiagara->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	StartNiagara->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	EndNiagara->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASoul::BeginPlay()
{
	Super::BeginPlay();

	MoveState = ESoulMoveState::MoveUpwards;
}

// Called every frame
void ASoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MoveState == ESoulMoveState::MoveUpwards) {
		Movable->SetWorldLocation(FVector(Movable->GetComponentLocation().X, Movable->GetComponentLocation().Y, Movable->GetComponentLocation().Z + SoulConfig->Speed * DeltaTime));

		if (Movable->GetComponentLocation().Z >= UpMoveTarget->GetComponentLocation().Z) {
			MoveState = ESoulMoveState::MoveTowardsSpline;
		}
	}
	else if (MoveState == ESoulMoveState::MoveTowardsSpline) {
		StartingPosition = Movable->GetComponentLocation();
		FVector ClosestSplinePoint = SoulRoute->GetClosestSplinePoint(StartingPosition);
		TargetPosition = ClosestSplinePoint;
		MoveState = ESoulMoveState::MovingTowardsSpline;

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartingPosition, TargetPosition);
		Movable->SetWorldRotation(LookAtRotation);
	}
	else if (MoveState == ESoulMoveState::MovingTowardsSpline) {
		FVector Direction = TargetPosition - StartingPosition;
		Direction.Normalize();
		FVector Position = Movable->GetComponentLocation() + Direction * SoulConfig->SpeedTowardsSpline * DeltaTime;
		FVector PreviousPosition = Movable->GetComponentLocation();
		Movable->SetWorldLocation(Position);

		FVector DirectionToTarget = (TargetPosition - PreviousPosition).GetSafeNormal();

		// Calculate the direction of movement
		FVector MovementDirection = (Movable->GetComponentLocation() -PreviousPosition).GetSafeNormal();

		if (FVector::DotProduct(DirectionToTarget, MovementDirection) <= 0.0f){
			MoveState = ESoulMoveState::MoveAlongSpline;
			ToSplineProgress = 0.f;
		}
	}
	else if (MoveState == ESoulMoveState::MoveAlongSpline) {
		float SplineLength = SoulRoute->GetRouteLengthOnSpline(TargetPosition);
		int index = SoulRoute->GetIndexOfSplinePoint(TargetPosition);
		float SplineDistance = SoulRoute->GetDistanceAlongSplineAtSplinePoint(index) + SplineLength * ToSplineProgress;
		FVector Position = SoulRoute->GetLocationAtDistanceAlongSpline(SplineDistance);
		FVector PreviousPosition = Movable->GetComponentLocation();
		Movable->SetWorldLocation(Position);
		ToSplineProgress += SoulConfig->SpeedAlongSpline * DeltaTime;

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(PreviousPosition, Movable->GetComponentLocation());
		Movable->SetWorldRotation(LookAtRotation);

		if (ToSplineProgress >= 1.0f) {
			MoveState = ESoulMoveState::MoveTowardsCollector;
			ToSplineProgress = 0.f;
		}
	}
	else if (MoveState == ESoulMoveState::MoveTowardsCollector) {

	}
}

void ASoul::SetSoulRoute(ASoulRoute* Route) {
	SoulRoute = Route;
}