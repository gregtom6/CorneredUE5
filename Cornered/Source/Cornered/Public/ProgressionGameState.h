// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Config_MixingMachine.h"
#include "ProgressionGameState.generated.h"

class UConfig_Progress;
class ACharacter;
/**
 *
 */
UCLASS()
class CORNERED_API AProgressionGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int UnlockLevel;
private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_Progress> ProgressConfig;

public:
	void ResetProgress();

	void StepProgress();

	void SaveProgress();

	UFUNCTION(BlueprintPure)
		bool IsAbilityAlreadyUnlocked(EAbility Ability);

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnCharacterDefeated(ACharacter* DefeatedCharacter);

};
