#include "Characters/StateTreeConditions/DefendPositionEnemyCondition.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "StateTreeConditionBase.h"
#include "Configs/DeveloperSettings/Config_CharacterSpawner.h"

bool FDefendPositionEnemyCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FStateTreeDefendConditionMagic* InstanceData = Context.GetInstanceDataPtr<FStateTreeDefendConditionMagic>(*this);

	if (!InstanceData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instance data or Source is missing"));
		return false;
	}

	return !InstanceData->bIsReadyToShoot || ((InstanceData->EnemyCurrentHealth / InstanceData->EnemyMaxHealth) * 100.f <= InstanceData->HideWhenLifeLessThanPercentage);
}