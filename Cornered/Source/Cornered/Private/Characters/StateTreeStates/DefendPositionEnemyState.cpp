// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/StateTreeStates/DefendPositionEnemyState.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeInstanceData.h"
#include "StateTreeTaskBase.h"
#include "Characters/Systems/EnemyController.h"
#include "Characters/Systems/EnemyCharacter.h"

EStateTreeRunStatus FDefendPositionEnemyState::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Context.GetOwner());
	AEnemyController* enemyController = Cast<AEnemyController>(EnemyCharacter->GetController());

	enemyController->HideFromPlayer();

	return EStateTreeRunStatus::Succeeded;
}

EStateTreeRunStatus FDefendPositionEnemyState::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Context.GetOwner());
	AEnemyController* enemyController = Cast<AEnemyController>(EnemyCharacter->GetController());

	enemyController->HideFromPlayer();

	return EStateTreeRunStatus::Running;
}