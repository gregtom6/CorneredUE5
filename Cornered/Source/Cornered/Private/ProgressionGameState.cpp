// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ProgressionGameState.h"
#include "EnemyCharacter.h"
#include "Config_Progress.h"
#include "CorneredGameMode.h"
#include "GameFramework/Character.h"

AProgressionGameState::AProgressionGameState() {

	
}

void AProgressionGameState::OnCharacterDefeated(ACharacter* DefeatedCharacter) {
	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {
		UnlockLevel = FMath::Clamp(UnlockLevel + 1, 0, ProgressConfig->GetMaxUnlockLevel());
	}
	else {
		ResetProgress();
	}
}

void AProgressionGameState::BeginPlay()
{
	Super::BeginPlay();

	UnlockLevel = 0;

	ACorneredGameMode* CorneredGameMode = GetWorld()->GetAuthGameMode<ACorneredGameMode>();

	CorneredGameMode->CharacterDefeated.AddDynamic(this, &AProgressionGameState::OnCharacterDefeated);
}

void AProgressionGameState::ResetProgress() {
	UnlockLevel = 0;
}

bool AProgressionGameState::IsAbilityAlreadyUnlocked(EAbility Ability) {

    return ProgressConfig->IsAbilityUnlocked(Ability, this);
}