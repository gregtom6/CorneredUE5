// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateTreeExecutionTypes.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "ShootPositionEnemyState.generated.h"

class UStruct;
class AEnemyCharacter;

USTRUCT()
struct FMyInstanceData
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		TObjectPtr<AEnemyCharacter> EnemyCharacter;
};

USTRUCT(DisplayName = "ShootPositionState")
struct CORNERED_API FShootPositionEnemyState : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

		using FInstanceDataType = FMyInstanceData;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
};
