// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "ProgressionGameState.h"
#include "EnemyCharacter.h"
#include "Config_Progress.h"

AProgressionGameState::AProgressionGameState() {

}

void AProgressionGameState::OnCharacterDefeated(AActor* DefeatedCharacter) {
	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {
		UnlockLevel = FMath::Clamp(UnlockLevel + 1, 0, ProgressConfig->GetMaxUnlockLevel());
	}
}

void AProgressionGameState::BeginPlay()
{
	Super::BeginPlay();

	UnlockLevel = 0;
}

void AProgressionGameState::ResetProgress() {
	UnlockLevel = 0;
}

bool AProgressionGameState::IsAbilityAlreadyUnlocked(EAbility Ability) {

    return ProgressConfig->IsAbilityUnlocked(Ability, this);
}