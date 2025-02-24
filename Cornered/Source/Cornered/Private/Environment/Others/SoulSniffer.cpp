// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Others/SoulSniffer.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/Systems/CharacterSpawner.h"
#include "Components/AudioComponent.h"
#include "ActorSequenceComponent.h"
#include "ActorSequencePlayer.h"
#include "Components/TextRenderComponent.h"
#include "Components/BoxComponent.h"
#include "Configs/DataAssets/Config_SoulSniffer.h"
#include "System/ProgressionGameState.h"
#include "System/CorneredGameInstance.h"
#include "Configs/DataAssets/Config_Progress.h"

// Sets default values
ASoulSniffer::ASoulSniffer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Target = CreateDefaultSubobject<USceneComponent>(TEXT("Target"));
	DissipateTarget = CreateDefaultSubobject<USceneComponent>(TEXT("DissipateTarget"));
	Led1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Led1"));
	Led2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Led2"));
	ProcessingLed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProcessingLed"));
	CatchAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("CatchAudioComp"));
	ProcessingAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("ProcessingAudioComp"));
	ProcessedAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("ProcessedAudioComp"));
	CountPassedBorderAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("CountPassedBorderAudioComp"));
	CurrentCountTextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CurrentCountTextComp"));
	SlashTextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("SlashTextComp"));
	BorderCountTextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BorderCountTextComp"));
	SoulDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("SoulDetector"));

	SetRootComponent(Root);
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Target->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	DissipateTarget->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Led1->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	Led2->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ProcessingLed->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	CatchAudioComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ProcessingAudioComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ProcessedAudioComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	CountPassedBorderAudioComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	CurrentCountTextComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	SlashTextComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	BorderCountTextComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	SoulDetector->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASoulSniffer::BeginPlay()
{
	Super::BeginPlay();

	SetBackDefaultState();

	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->SetSoulSniffer(this);
	}

	SoulDetector->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASoulSniffer::OnEnterDetectorBeginOverlap);

	State = ESoulSnifferState::Disabled;

	int32 currentBordercount = ProgressConfig->GetSoulBorderCount(GetWorld());

	FString borderCountInString = FormatNumber(currentBordercount, SnifferConfig->DigitNumber);

	BorderCountTextComp->SetText(FText::FromString(borderCountInString));

	PrintCurrentSniffedSoulCount();
}

// Called every frame
void ASoulSniffer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoulSniffer::OnEnterDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASoulSniffer::SoulCatched, SnifferConfig->TimeBeforeCatchSoul, false);
}

void ASoulSniffer::SoulCatched() {
	CatchSequenceComp->PlaySequence();

	CatchAudioComp->Play();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASoulSniffer::SoulProcessing, SnifferConfig->TimeBetweenCatchAndProcess, false);
}

void ASoulSniffer::SoulProcessing() {
	UActorSequencePlayer* SequencePlayer = ProcessingSequenceComp->GetSequencePlayer();
	SequencePlayer->PlayLooping();
	ProcessingAudioComp->Play();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASoulSniffer::StopSoulProcessing, SnifferConfig->TimeForProcess, false);
}

void ASoulSniffer::StopSoulProcessing() {

	ProcessingSequenceComp->StopSequence();

	ProcessingAudioComp->Stop();

	ProcessingLed->SetMaterial(0, SnifferConfig->DisabledGreyLight);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASoulSniffer::SoulProcessed, SnifferConfig->TimeAfterProcess, false);
}

void ASoulSniffer::SoulProcessed() {
	ProcessedSequenceComp->PlaySequence();

	ProcessedAudioComp->Play();

	SlashTextComp->SetMaterial(0, SnifferConfig->ActiveWhiteText);

	BorderCountTextComp->SetMaterial(0, SnifferConfig->ActiveRedText);

	PrintCurrentSniffedSoulCount();

	AProgressionGameState* MyGameState = Cast<AProgressionGameState>(GetWorld()->GetGameState());
	if (MyGameState)
	{
		int32 currentSniffedSoulCount = MyGameState->GetCurrentSniffedSoulCount();

		UMaterialInterface* SelectedMaterial = nullptr;

		UCorneredGameInstance* MyGameInstance = Cast<UCorneredGameInstance>(GetWorld()->GetGameInstance());

		if (currentSniffedSoulCount > ProgressConfig->GetSoulBorderCount(GetWorld())) {
			SelectedMaterial = SnifferConfig->ActiveRedText;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &ASoulSniffer::CountPassedBorder, SnifferConfig->TimeUntilAlarm, false);
		}
		else {
			SelectedMaterial = SnifferConfig->ActiveGreenText;
		}

		CurrentCountTextComp->SetMaterial(0, SelectedMaterial);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASoulSniffer::SetBackDefaultState, SnifferConfig->TimeForTextBrightness, false);
}

void ASoulSniffer::CountPassedBorder() {
	CountPassedBorderAudioComp->Play();

	AlarmSequenceComp->PlaySequence();
}

void ASoulSniffer::PrintCurrentSniffedSoulCount() {
	AProgressionGameState* MyGameState = Cast<AProgressionGameState>(GetWorld()->GetGameState());

	if (MyGameState) {
		int32 currentSniffedSoulCount = MyGameState->GetCurrentSniffedSoulCount();

		FString stringVersion = FormatNumber(currentSniffedSoulCount, SnifferConfig->DigitNumber);

		CurrentCountTextComp->SetText(FText::FromString(stringVersion));
	}
}

void ASoulSniffer::SetBackDefaultState() {
	CurrentCountTextComp->SetMaterial(0, SnifferConfig->DisabledGreyText);

	SlashTextComp->SetMaterial(0, SnifferConfig->DisabledGreyText);

	BorderCountTextComp->SetMaterial(0, SnifferConfig->DisabledGreyText);
}

FVector ASoulSniffer::GetTargetLocation() {
	return Target->GetComponentLocation();
}

FVector ASoulSniffer::GetDissipateTargetLocation() {
	return DissipateTarget->GetComponentLocation();
}

FString ASoulSniffer::FormatNumber(int32 Number, int32 Digits)
{
	return FString::Printf(TEXT("%0*ld"), Digits, Number);
}