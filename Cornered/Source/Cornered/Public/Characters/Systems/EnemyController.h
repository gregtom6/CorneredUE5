// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "System/CorneredPlayerController.h"
#include "Characters/Systems/MovableCharacter.h"
#include "EnemyController.generated.h"

class ACorneredGameMode;
class UPathFollowingComponent;
class AEnemyCharacter;
class UStateTreeComponent;
class UConfig_AI;

UCLASS()
class CORNERED_API AEnemyController : public AAIController, public IMovableCharacter
{
	GENERATED_BODY()

protected:
	bool bIsTimerOver;

private:
	EMovementState MovementState;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_AI> AIConfig;

public:
	AEnemyController();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
		virtual EMovementState GetMovementState() const override;

	UFUNCTION(BlueprintCallable)
		void FollowPlayer();

	UFUNCTION(BlueprintCallable)
		void HideFromPlayer();

protected:

	UFUNCTION()
		void OnTimerOverHappened();

	virtual void BeginPlay() override;
};
