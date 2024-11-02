// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Gates/CorridorHider.h"
#include "System/CorneredGameMode.h"
#include "System/ProgressionGameState.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ACorridorHider::ACorridorHider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	WallLeftComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallLeftComp"));
	WallRightComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallRightComp"));

	SetRootComponent(Root);
	WallLeftComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	WallRightComp->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACorridorHider::BeginPlay()
{
	Super::BeginPlay();
	
	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
	AGameStateBase* GameState = GetWorld()->GetGameState();
	AProgressionGameState* ProgressionGameState = Cast<AProgressionGameState>(GameState);

	CorneredGameMode->TimeOverHappened.AddUniqueDynamic(this, &ACorridorHider::OnTimerOverHappened);
	ProgressionGameState->CharacterDefeated.AddUniqueDynamic(this, &ACorridorHider::OnCharacterDefeated);

	ManageMeshes(true);
}

void ACorridorHider::OnTimerOverHappened()
{
	ManageMeshes(false);
}

void ACorridorHider::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {

	if (DefeatedCharacter->IsA<APlayerCharacter>()) {
		return;
	}

	ManageMeshes(true);
}

void ACorridorHider::ManageMeshes(bool activate) {
	WallLeftComp->Activate(activate);
	WallRightComp->Activate(activate);
}