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
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TObjectPtr<UActorSequenceComponent> OpenSequ;
private:


	UPROPERTY(EditAnywhere)
		TObjectPtr<USceneComponent> Root;

public:	
	// Sets default values for this actor's properties
	AExitButtonMover();

		void StartMoving();

};
