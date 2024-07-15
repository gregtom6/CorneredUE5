// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RedLightController.generated.h"

class UActorSequenceComponent;
class UActorSequencePlayer;

UCLASS()
class CORNERED_API ARedLightController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARedLightController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTimerOverHappened();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		UActorSequenceComponent* DisabledSequ;
	UPROPERTY()
		UActorSequenceComponent* BlinkingSequ;

private:
	FTimerHandle TimerHandle;
};
