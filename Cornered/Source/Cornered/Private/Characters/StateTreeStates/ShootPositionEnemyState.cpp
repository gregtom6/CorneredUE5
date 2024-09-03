// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/StateTreeStates/ShootPositionEnemyState.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Characters/Systems/EnemyController.h"

EStateTreeRunStatus FShootPositionEnemyState::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Context.GetOwner());
	AEnemyController* enemyController = Cast<AEnemyController>(EnemyCharacter->GetController());

	enemyController->FollowPlayer();

	return EStateTreeRunStatus::Succeeded;
}