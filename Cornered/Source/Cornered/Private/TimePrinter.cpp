// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "TimePrinter.h"
#include "Components/TextRenderComponent.h"
#include "CorneredGameMode.h"

// Sets default values
ATimePrinter::ATimePrinter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TimeLeftComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TimeLeftComp"));

	SetRootComponent(Root);
	TimeLeftComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ATimePrinter::BeginPlay()
{
	Super::BeginPlay();

	CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
	
}

// Called every frame
void ATimePrinter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CorneredGameMode) {

		float timeLeft = CorneredGameMode->GetPreparingTimeLeft();

		int32 IntValue = FMath::RoundToInt(timeLeft);

		FString stringVersion = FString::FromInt(IntValue);

		TimeLeftComp->SetText(FText::FromString(stringVersion));
	}
	
}

