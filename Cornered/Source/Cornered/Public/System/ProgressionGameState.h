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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoulSniffedDelegate);

/**
 *
 */
UCLASS()
class CORNERED_API AProgressionGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 UnlockLevel;

	UPROPERTY()
	int32 SoulSniffedCount;

	FCharacterDefeatedDelegate CharacterDefeated;

	FCharacterShotReceivedDelegate CharacterShotReceived;

	FSoulSniffedDelegate SoulSniffed;

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Progress> ProgressConfig;

public:

	void SaveProgress();

	UFUNCTION(BlueprintPure)
	bool IsAbilityAlreadyUnlocked(EAbility Ability);

	UFUNCTION(BlueprintPure)
	int32 GetCurrentSniffedSoulCount() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentOverloadSoulCount() const;

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);
	UFUNCTION()
	void OnCharacterShotReceived(ACorneredCharacter* CharacterReceivedShot);
	UFUNCTION()
	void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);
	UFUNCTION()
	void OnSoulSniffed();

	void SubscribeToCharacterDamageDelegates(ACorneredCharacter* Character);

	void StepUnlockLevel();
	void ResetProgress();
	void ResetUnlockLevel();
};
