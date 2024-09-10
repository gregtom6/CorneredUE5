// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PostProcessController.generated.h"

class ACorneredCharacter;
class UCameraComponent;
class UConfig_Time;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UPostProcessController : public UActorComponent
{
	GENERATED_BODY()

private:
	TObjectPtr<UCameraComponent> Camera;

	bool bPlayerDied = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Time> TimeConfig;

	float TimeWhenPlayerDied;

public:	
	// Sets default values for this component's properties
	UPostProcessController();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:

	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);
};
