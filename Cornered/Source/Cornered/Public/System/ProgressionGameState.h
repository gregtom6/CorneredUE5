// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Configs/DataAssets/Config_MixingMachine.h"
#include "ProgressionGameState.generated.h"

class UConfig_Progress;
class ACorneredCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDefeatedDelegate, ACorneredCharacter*, Character);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterShotReceivedDelegate, ACorneredCharacter*, Character);

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

	FCharacterDefeatedDelegate CharacterDefeated;

	FCharacterShotReceivedDelegate CharacterShotReceived;

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
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);
	UFUNCTION()
	void OnCharacterShotReceived(ACorneredCharacter* CharacterReceivedShot);
	UFUNCTION()
	void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

	void SubscribeToCharacterDamageDelegates(ACorneredCharacter* Character);
};
