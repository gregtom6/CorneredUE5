// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "BeltController.h"
#include "Components/BoxComponent.h"
#include "Config_Belt.h"
#include "CorneredObjectPool.h"
#include "BeltElement.h"
#include "CorneredButton.h"

// Sets default values
ABeltController::ABeltController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPointComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPointComp"));

	DespawnPointComp = CreateDefaultSubobject<UBoxComponent>(TEXT("DespawnPointComp"));

	DespawnPointComp->OnComponentBeginOverlap.AddDynamic(this, &ABeltController::OnOverlapBegin);
	SpawnPointComp->OnComponentEndOverlap.AddDynamic(this, &ABeltController::OnOverlapEnd);
}

// Called when the game starts or when spawned
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
	ABeltElement* beltElementComp = Cast<ABeltElement>(beltElement);
	beltElementComp->SetBeltController(this);
	beltElement->SetActorLocation(SpawnPointComp->GetComponentLocation());
}

void ABeltController::PressHappened() {
	SwitchBeltSpeed();
}

void ABeltController::SwitchBeltSpeed() {
	CurrentBeltSpeed = CurrentBeltSpeed == EBeltSpeed::Normal ? EBeltSpeed::Fastened : EBeltSpeed::Normal;
}

// Called every frame
void ABeltController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

float ABeltController::GetCurrentMultiplier()
{
	return BeltConfig->GetCurrentMultiplier(CurrentBeltSpeed);
}

void ABeltController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->IsA<ABeltElement>() && ObjectPool)
	{
		ObjectPool->RecycleActor(OtherActor);
	}
}

void ABeltController::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->IsA<ABeltElement>() && ObjectPool && this)
	{
		AActor* beltElement = ObjectPool->GetPooledActor("BP_BeltElement");

		if (beltElement) {
			beltElement->SetActorLocation(SpawnPointComp->GetComponentLocation());
			beltElement->SetActorHiddenInGame(false);
			beltElement->SetActorEnableCollision(true);
			beltElement->SetActorTickEnabled(true);
			ABeltElement* beltElementComp = Cast<ABeltElement>(beltElement);
			beltElementComp->SetBeltController(this);
		}
	}
}

EBeltSpeed ABeltController::GetCurrentBeltSpeed() {
	return CurrentBeltSpeed;
}