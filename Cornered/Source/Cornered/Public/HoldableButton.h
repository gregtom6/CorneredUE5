// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Holdable.h"
#include "HoldableButton.generated.h"

class AHoldActivable;

UCLASS()
class CORNERED_API AHoldableButton : public AActor, public IHoldable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHoldableButton();

public:	

	virtual void HoldingStarted() override;

	virtual void HoldingFinished() override;

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<AHoldActivable> HoldActivable;

};
