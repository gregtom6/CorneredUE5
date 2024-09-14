#include "Characters/StateTreeConditions/PlayerDeathEnemyCondition.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include <Kismet/GameplayStatics.h>

bool FPlayerDeathEnemyCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(Context.GetWorld(), 0);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);

	if (PlayerCharacter) {
		UCharacterHealth* Health = PlayerCharacter->CharacterHealth;
		if (Health) {
			return Health->GetCurrentHealth() <= 0.f;
		}
	}

	return false;
}