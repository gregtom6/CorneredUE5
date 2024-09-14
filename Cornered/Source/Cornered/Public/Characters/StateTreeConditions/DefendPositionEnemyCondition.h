#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "StateTreeConditionBase.h"
#include "DefendPositionEnemyCondition.generated.h"

class UStruct;

USTRUCT()
struct FStateTreeDefendConditionData
{
	GENERATED_BODY()

	FStateTreeDefendConditionData()
		: EnemyCurrentHealth(0.f), EnemyMaxHealth(0.f), HideWhenLifeLessThanPercentage(0.f), bIsReadyToShoot(false) { }

	UPROPERTY(EditAnywhere, Category = "Input")
	float EnemyCurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Input")
	float EnemyMaxHealth;

	UPROPERTY(EditAnywhere, Category = "Input")
	float HideWhenLifeLessThanPercentage;

	UPROPERTY(EditAnywhere, Category = "Input")
	bool bIsReadyToShoot;
};


USTRUCT(DisplayName = "DefendPositionCondition")
struct FDefendPositionEnemyCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FConditionData = FStateTreeDefendConditionData;

	virtual const UStruct* GetInstanceDataType() const override { return FConditionData::StaticStruct(); }

public:

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};