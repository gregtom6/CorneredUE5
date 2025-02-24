// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PostProcessController.generated.h"

class ACorneredCharacter;
class UCameraComponent;
class UConfig_Time;
class UConfig_Visual;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UPostProcessController : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TObjectPtr<UCameraComponent> Camera;

	bool bPlayerDied = false;

	bool bPlayerShotReceived = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Time> TimeConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Visual> VisualConfig;

	float TimeWhenPostProcessStarted;

public:	
	// Sets default values for this component's properties
	UPostProcessController();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnCharacterShotReceived(ACorneredCharacter* CharacterReceivedShot);
	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);

	void ProcessWhenPlayerDied();

	void ProcessWhenShotReceived();
};
