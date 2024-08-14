#include "ShootPositionEnemyCondition.h"

FShootPositionEnemyCondition::FShootPositionEnemyCondition()
{
	
}

bool FShootPositionEnemyCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	// Retrieve instance data from the context
	const FStateTreeConditionMagic* InstanceData = Context.GetInstanceDataPtr<FStateTreeConditionMagic>(*this);

	// Check if instance data is valid
	if (!InstanceData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instance data or Source is missing"));
		return false;
	}

	return (InstanceData->EnemyCurrentHealth / InstanceData->EnemyMaxHealth) * 100.f >= InstanceData->AttackWhenLifeMoreThanPercentage && InstanceData->bIsReadyToShoot;
}