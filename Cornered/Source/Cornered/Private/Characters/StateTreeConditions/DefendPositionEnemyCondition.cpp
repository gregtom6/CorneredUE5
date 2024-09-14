#include "Characters/StateTreeConditions/DefendPositionEnemyCondition.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "StateTreeConditionBase.h"
#include "Configs/DeveloperSettings/Config_CharacterSpawner.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include <Kismet/GameplayStatics.h>

bool FDefendPositionEnemyCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FStateTreeDefendConditionData* InstanceData = Context.GetInstanceDataPtr<FStateTreeDefendConditionData>(*this);

	if (!InstanceData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instance data or Source is missing"));
		return false;
	}

	if (InstanceData->EnemyCurrentHealth <= 0.f) {
		return false;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(Context.GetWorld(), 0);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);

	if (PlayerCharacter) {
		UCharacterHealth* Health = PlayerCharacter->CharacterHealth;
		if (Health && Health->GetCurrentHealth() <= 0.f) {
			return false;
		}
	}

	return !InstanceData->bIsReadyToShoot || ((InstanceData->EnemyCurrentHealth / InstanceData->EnemyMaxHealth) * 100.f <= InstanceData->HideWhenLifeLessThanPercentage);
}