// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/PostProcessController.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"
#include "Configs/DataAssets/Config_Time.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Configs/DataAssets/Config_Visual.h"
#include "System/ProgressionGameState.h"

// Sets default values for this component's properties
UPostProcessController::UPostProcessController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPostProcessController::BeginPlay()
{
	Super::BeginPlay();

	AGameStateBase* GameState = GetWorld()->GetGameState();
	AProgressionGameState* ProgressionGameState = Cast<AProgressionGameState>(GameState);
	ProgressionGameState->CharacterDefeated.AddUniqueDynamic(this, &UPostProcessController::OnCharacterDefeated);
	ProgressionGameState->CharacterShotReceived.AddUniqueDynamic(this, &UPostProcessController::OnCharacterShotReceived);

	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
}

// Called every frame
void UPostProcessController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ProcessWhenPlayerDied();
	
	ProcessWhenShotReceived();
}

void UPostProcessController::ProcessWhenPlayerDied() {
	if (!bPlayerDied) {
		return;
	}

	float currentTime = GetWorld()->GetTimeSeconds() - TimeWhenPostProcessStarted;
	float percentage = currentTime / TimeConfig->WaitTimeUntilGameOver;
	percentage = FMath::Clamp(percentage, 0.f, 1.f);

	for (int i = 0; i < Camera->PostProcessSettings.WeightedBlendables.Array.Num(); i++) {
		Camera->PostProcessSettings.WeightedBlendables.Array[i].Weight = percentage;
	}
}

void UPostProcessController::ProcessWhenShotReceived() {
	if (bPlayerDied || !bPlayerShotReceived) {
		return;
	}

	float currentTime = GetWorld()->GetTimeSeconds() - TimeWhenPostProcessStarted;
	float percentage = currentTime / TimeConfig->ReceivingHitPostProcessTime;
	percentage = FMath::Clamp(percentage, 0.f, 1.f);
	float valueToUse = VisualConfig->PlayerReceivedShotPostProcessMultiplier - (percentage * VisualConfig->PlayerReceivedShotPostProcessMultiplier);

	for (int i = 0; i < Camera->PostProcessSettings.WeightedBlendables.Array.Num(); i++) {
		Camera->PostProcessSettings.WeightedBlendables.Array[i].Weight = valueToUse;
	}
}

void UPostProcessController::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {

	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {
		return;
	}

	bPlayerDied = true;
	TimeWhenPostProcessStarted = GetWorld()->GetTimeSeconds();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->PlayerCameraManager->StartCameraFade(0.f, 1.f, TimeConfig->WaitTimeUntilGameOver, FLinearColor::Black, false, true);
}

void UPostProcessController::OnCharacterShotReceived(ACorneredCharacter* CharacterReceivedShot) {
	if (CharacterReceivedShot->IsA<AEnemyCharacter>() ||
		bPlayerDied) {
		return;
	}

	bPlayerShotReceived = true;
	TimeWhenPostProcessStarted = GetWorld()->GetTimeSeconds();
}