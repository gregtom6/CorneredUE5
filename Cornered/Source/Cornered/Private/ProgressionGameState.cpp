// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ProgressionGameState.h"
#include "EnemyCharacter.h"
#include "Config_Progress.h"
#include "CorneredGameMode.h"
#include "GameFramework/Character.h"
#include "CorneredGameInstance.h"

AProgressionGameState::AProgressionGameState() {

	
}

void AProgressionGameState::OnCharacterDefeated(ACharacter* DefeatedCharacter) {

	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {
		StepProgress();
	}
	else {
		ResetProgress();
	}
}

void AProgressionGameState::BeginPlay()
{
	Super::BeginPlay();

	ResetProgress();

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	CorneredGameMode->CharacterDefeated.AddDynamic(this, &AProgressionGameState::OnCharacterDefeated);
}

void AProgressionGameState::ResetProgress() {
	
	UnlockLevel = 0;

	SaveProgress();
}

void AProgressionGameState::StepProgress() {

	UnlockLevel = FMath::Clamp(UnlockLevel + 1, 0, ProgressConfig->GetMaxUnlockLevel());

	SaveProgress();
}

void AProgressionGameState::SaveProgress() {
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	UGameInstance* GameInstance = GameMode->GetGameInstance();

	UCorneredGameInstance* CorneredGameInstance = Cast<UCorneredGameInstance>(GameInstance);

	CorneredGameInstance->SaveGame(UnlockLevel);
}

bool AProgressionGameState::IsAbilityAlreadyUnlocked(EAbility Ability) {

    return ProgressConfig->IsAbilityUnlocked(Ability, this);
}