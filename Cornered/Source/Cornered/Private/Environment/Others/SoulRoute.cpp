// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Others/SoulRoute.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Characters/Systems/CharacterSpawner.h"

// Sets default values
ASoulRoute::ASoulRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));

	SetRootComponent(Root);
	SplineComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASoulRoute::BeginPlay()
{
	Super::BeginPlay();
	
	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->SetSoulRoute(this);
	}
}

// Called every frame
void ASoulRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASoulRoute::GetSplinePoint(int32 index) const {
	return SplineComp->GetLocationAtSplinePoint(index,ESplineCoordinateSpace::World);
}

FVector ASoulRoute::GetClosestSplinePoint(FVector Position) {

	float Distance = FVector::Distance(Position, GetSplinePoint(0));
	FVector Selected = GetSplinePoint(0);

	for (int i = 1; i < SplineComp->GetNumberOfSplinePoints(); i++) {
		if (FVector::Distance(Position, GetSplinePoint(i)) < Distance) {
			Distance = FVector::Distance(Position, GetSplinePoint(i));
			Selected = GetSplinePoint(i);
		}
	}

	return Selected;
}

int32 ASoulRoute::GetIndexOfSplinePoint(FVector Point) {
	for (int i = 0; i < SplineComp->GetNumberOfSplinePoints(); i++) {

		FVector Position = GetSplinePoint(i);

		if (FMath::IsNearlyEqual(Position.X, Point.X) &&
			FMath::IsNearlyEqual(Position.Y, Point.Y) &&
			FMath::IsNearlyEqual(Position.Z, Point.Z)) {
			return i;
		}
	}

	return -1;
}

float ASoulRoute::GetRouteLengthOnSpline(FVector StartPos) {

	int32 index = GetIndexOfSplinePoint(StartPos);

	return SplineComp->GetDistanceAlongSplineAtSplinePoint(SplineComp->GetNumberOfSplinePoints() - 1) - SplineComp->GetDistanceAlongSplineAtSplinePoint(index);
}

FVector ASoulRoute::GetLocationAtDistanceAlongSpline(float distance) {
	return SplineComp->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
}

float ASoulRoute::GetDistanceAlongSplineAtSplinePoint(int32 index) {
	return SplineComp->GetDistanceAlongSplineAtSplinePoint(index);
}