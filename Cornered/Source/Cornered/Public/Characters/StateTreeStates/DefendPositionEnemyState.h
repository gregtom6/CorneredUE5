// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "DefendPositionEnemyState.generated.h"

class UStruct;

USTRUCT()
struct FDefendTest
{
	GENERATED_BODY()
};

USTRUCT(DisplayName = "DefendPositionState")
struct CORNERED_API FDefendPositionEnemyState : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

		using FInstanceDataType = FDefendTest;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
};
