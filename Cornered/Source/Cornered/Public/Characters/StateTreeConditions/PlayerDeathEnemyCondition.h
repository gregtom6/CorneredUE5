#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "StateTreeConditionBase.h"
#include "PlayerDeathEnemyCondition.generated.h"

class UStruct;
class APlayerCharacter;

USTRUCT()
struct FStateTreePlayerDeathConditionData
{
	GENERATED_BODY()
};


USTRUCT(DisplayName = "PlayerDeathEnemyCondition")
struct FPlayerDeathEnemyCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FConditionData = FStateTreePlayerDeathConditionData;

	virtual const UStruct* GetInstanceDataType() const override { return FConditionData::StaticStruct(); }

public:

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};