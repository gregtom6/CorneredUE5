// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/ConveyorBelt/BeltController.h"
#include "Components/BoxComponent.h"
#include "Configs/DataAssets/Config_Belt.h"
#include "System/CorneredObjectPool.h"
#include "System/CorneredPooledObject.h"
#include "Environment/ConveyorBelt/BeltElement.h"
#include "Environment/Interactables/CorneredButton.h"

ABeltController::ABeltController()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnPointComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPointComp"));
	DespawnPointComp = CreateDefaultSubobject<UBoxComponent>(TEXT("DespawnPointComp"));

	DespawnPointComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABeltController::OnOverlapBegin);
	SpawnPointComp->OnComponentEndOverlap.AddUniqueDynamic(this, &ABeltController::OnOverlapEnd);
}

void ABeltController::BeginPlay()
{
	Super::BeginPlay();

	CurrentBeltSpeed = EBeltSpeed::Normal;

	CorneredButton->PressHappened.AddUniqueDynamic(this, &ABeltController::PressHappened);
	ObjectPool->InitializationHappened.AddUniqueDynamic(this, &ABeltController::ObjectPoolInitialized);

	if (ObjectPool->bAlreadyInitialized) {
		ObjectPoolInitialized();
	}
}

void ABeltController::ObjectPoolInitialized() {
	AActor* beltElement = ObjectPool->GetPooledActor("BP_BeltElement");
	beltElement->SetActorLocation(SpawnPointComp->GetComponentLocation());

	CurrentlyVisibleBeltElements.Add(beltElement);
}

void ABeltController::PressHappened() {
	SwitchBeltSpeed();
}

void ABeltController::SwitchBeltSpeed() {
	CurrentBeltSpeed = CurrentBeltSpeed == EBeltSpeed::Normal ? EBeltSpeed::Fastened : EBeltSpeed::Normal;
}

float ABeltController::GetCurrentMultiplier() const
{
	return BeltConfig->GetCurrentMultiplier(CurrentBeltSpeed);
}

void ABeltController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	for (int i = 0; i < CurrentlyVisibleBeltElements.Num(); i++) {
		AActor* currentBeltElement = CurrentlyVisibleBeltElements[i];

		if (currentBeltElement) {
			float currentBeltSpeed = GetCurrentMultiplier();

			FVector NewLocation = currentBeltElement->GetActorLocation() + (currentBeltSpeed * DeltaTime * GetActorForwardVector());
			currentBeltElement->SetActorLocation(NewLocation);
		}
	}
}

void ABeltController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->IsA<ABeltElement>() && ObjectPool)
	{
		ObjectPool->RecycleActor(OtherActor);

		CurrentlyVisibleBeltElements.Remove(OtherActor);
	}
}

void ABeltController::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GetWorld() && !GetWorld()->bIsTearingDown && OtherActor && (OtherActor != this) && OtherComp && OtherActor->IsA<ABeltElement>() && ObjectPool && this)
	{
		AActor* beltElement = ObjectPool->GetPooledActor("BP_BeltElement");

		if (beltElement) {
			beltElement->SetActorLocation(SpawnPointComp->GetComponentLocation());
			beltElement->SetActorHiddenInGame(false);
			beltElement->SetActorEnableCollision(true);
			beltElement->SetActorTickEnabled(true);
			UCorneredPooledObject* pooledObject = beltElement->GetComponentByClass<UCorneredPooledObject>();
			if (pooledObject) {
				pooledObject->Activated.Broadcast();
			}

			CurrentlyVisibleBeltElements.Add(beltElement);
		}
	}
}

EBeltSpeed ABeltController::GetCurrentBeltSpeed() const {
	return CurrentBeltSpeed;
}