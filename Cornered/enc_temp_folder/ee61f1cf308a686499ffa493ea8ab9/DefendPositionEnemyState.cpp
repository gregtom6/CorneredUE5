// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "DefendPositionEnemyState.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeInstanceData.h"
#include "StateTreeTaskBase.h"
#include "EnemyController.h"
#include "EnemyCharacter.h"

EStateTreeRunStatus FDefendPositionEnemyState::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	if (Context.IsValid()) {
		FDefendTest* Data = Context.GetInstanceDataPtr<FDefendTest>(*this);

		AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Context.GetOwner());

		AEnemyController* enemyController = Cast<AEnemyController>(EnemyCharacter->GetController());

		enemyController->HideFromPlayer();

		return EStateTreeRunStatus::Succeeded;
	}

	return EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus FDefendPositionEnemyState::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	FDefendTest& InstanceData = Context.GetInstanceData<FDefendTest>(*this);

	AController* enemyControllerPawn = InstanceData.EnemyCharacter->GetController();

	AEnemyController* enemyController = Cast<AEnemyController>(enemyControllerPawn);

	enemyController->HideFromPlayer();

	return EStateTreeRunStatus::Running;
}