// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Environment/Interactables/Holdable.h"
#include "HoldableButton.generated.h"

class AHoldActivable;
class UActorSequenceComponent;
class UActorSequencePlayer;

UCLASS()
class CORNERED_API AHoldableButton : public AActor, public IHoldable
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> ButtonPushComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> ButtonReleaseComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> ButtonRotateComp;

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<AHoldActivable> HoldActivable;

public:
	// Sets default values for this actor's properties
	AHoldableButton();

	virtual void HoldingStarted() override;

	virtual void HoldingFinished() override;

};
