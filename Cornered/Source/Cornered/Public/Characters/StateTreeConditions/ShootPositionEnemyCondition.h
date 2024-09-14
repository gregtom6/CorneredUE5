#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "StateTreeConditionBase.h"
#include "ShootPositionEnemyCondition.generated.h"

class UStruct;

USTRUCT()
struct FStateTreeShootConditionData
{
	GENERATED_BODY()

	FStateTreeShootConditionData()
		: EnemyCurrentHealth(0.f), EnemyMaxHealth(0.f), AttackWhenLifeMoreThanPercentage(0.f), bIsReadyToShoot(false) { }

	UPROPERTY(EditAnywhere, Category = "Input")
	float EnemyCurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Input")
	float EnemyMaxHealth;

	UPROPERTY(EditAnywhere, Category = "Input")
	float AttackWhenLifeMoreThanPercentage;

	UPROPERTY(EditAnywhere, Category = "Input")
	bool bIsReadyToShoot;

};

USTRUCT(DisplayName = "ShootPositionCondition")
struct FShootPositionEnemyCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FConditionData = FStateTreeShootConditionData;

	virtual const UStruct* GetInstanceDataType() const override { return FConditionData::StaticStruct(); }

public:

	// This function is where the actual condition logic will be implemented
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};