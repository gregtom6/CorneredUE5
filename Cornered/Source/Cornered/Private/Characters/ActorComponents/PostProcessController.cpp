// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/PostProcessController.h"
#include "System/CorneredGameMode.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"
#include "Configs/DataAssets/Config_Time.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values for this component's properties
UPostProcessController::UPostProcessController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPostProcessController::BeginPlay()
{
	Super::BeginPlay();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();
	CorneredGameMode->CharacterDefeated.AddUniqueDynamic(this, &UPostProcessController::OnCharacterDefeated);

	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
}

// Called every frame
void UPostProcessController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bPlayerDied) {
		return;
	}

	float currentTime = GetWorld()->GetTimeSeconds() - TimeWhenPlayerDied;
	float percentage = currentTime / TimeConfig->WaitTimeUntilGameOver;
	percentage = FMath::Clamp(percentage, 0.f, 1.f);

	for (int i = 0; i < Camera->PostProcessSettings.WeightedBlendables.Array.Num(); i++) {
		Camera->PostProcessSettings.WeightedBlendables.Array[i].Weight = percentage;
	}

}

void UPostProcessController::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {

	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {
		return;
	}

	bPlayerDied = true;
	TimeWhenPlayerDied = GetWorld()->GetTimeSeconds();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->PlayerCameraManager->StartCameraFade(0.f, 1.f, TimeConfig->WaitTimeUntilGameOver, FLinearColor::Black, false, true);
}