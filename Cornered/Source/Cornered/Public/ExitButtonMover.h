// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExitButtonMover.generated.h"

class UActorSequenceComponent;
class UActorSequencePlayer;

UCLASS()
class CORNERED_API AExitButtonMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitButtonMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
		void StartMoving();

private:

	UPROPERTY()
		TObjectPtr<UActorSequenceComponent> OpenSequ;

	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> Root;
};
