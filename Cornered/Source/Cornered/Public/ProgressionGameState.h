// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Config_MixingMachine.h"
#include "ProgressionGameState.generated.h"

class UConfig_Progress;

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

	AProgressionGameState();

	UFUNCTION()
		void ResetProgress();

	UFUNCTION()
		bool IsAbilityAlreadyUnlocked(EAbility Ability);

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnCharacterDefeated(AActor* DefeatedCharacter);

	UPROPERTY(EditAnywhere)
		UConfig_Progress* ProgressConfig;
};
