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
struct FStateTreeDefendConditionMagic
{
	GENERATED_BODY()

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

		using FMyMagic = FStateTreeDefendConditionMagic;

	virtual const UStruct* GetInstanceDataType() const override { return FMyMagic::StaticStruct(); }

public:

	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};