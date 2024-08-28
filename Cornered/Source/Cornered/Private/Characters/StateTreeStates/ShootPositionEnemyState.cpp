// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/StateTreeStates/ShootPositionEnemyState.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Characters/Systems/EnemyController.h"

// Implement the EnterState function, which will be called when this state is entered.
EStateTreeRunStatus FShootPositionEnemyState::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FMyInstanceData& InstanceData = Context.GetInstanceData<FMyInstanceData>(*this);

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Context.GetOwner());

	AEnemyController* enemyController = Cast<AEnemyController>(EnemyCharacter->GetController());

	enemyController->FollowPlayer();

	return EStateTreeRunStatus::Succeeded;
}