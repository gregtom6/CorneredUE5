// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "CorneredPlayerController.h"
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

	UFUNCTION()
		EMovementState GetMovementState() const;

protected:

	UFUNCTION()
		void OnTimerOverHappened();

	UFUNCTION()
		void FollowPlayer();

	virtual void BeginPlay() override;

	bool bIsTimerOver;

private:

	UPROPERTY()
		EMovementState MovementState;
};
