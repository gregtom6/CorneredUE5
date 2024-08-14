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
struct FStateTreeConditionMagic
{
	GENERATED_BODY()

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

		using FMyMagic = FStateTreeConditionMagic;

	virtual const UStruct* GetInstanceDataType() const override { return FMyMagic::StaticStruct(); }

public:

	// Constructor
	FShootPositionEnemyCondition();

	// This function is where the actual condition logic will be implemented
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};