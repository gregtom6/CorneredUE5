// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "CorneredPlayerController.h"
#include "EnemyController.generated.h"

class ACorneredGameMode;
class UPathFollowingComponent;
class AEnemyCharacter;
class UStateTreeComponent;
class UConfig_AI;
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

	UFUNCTION()
		void FollowPlayer();

	UFUNCTION()
		void HideFromPlayer();

protected:

	UFUNCTION()
		void OnTimerOverHappened();


	virtual void BeginPlay() override;

	bool bIsTimerOver;

private:

		EMovementState MovementState;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_AI> AIConfig;
};
