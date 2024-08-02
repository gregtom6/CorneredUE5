// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class ACorneredGameMode;

/**
 * 
 */
UCLASS()
class CORNERED_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

protected:

	UFUNCTION()
		void OnTimerOverHappened();

	virtual void BeginPlay() override;
};
