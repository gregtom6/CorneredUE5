// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnemyController.generated.h"

class ACorneredGameMode;
class UPathFollowingComponent;

/**
 * 
 */
UCLASS()
class CORNERED_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION()
		void OnTimerOverHappened();

	virtual void BeginPlay() override;

		void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
};
