// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "CorneredButton.generated.h"

class UAudioComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressHappenedDelegate);

UCLASS()
class CORNERED_API ACorneredButton : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ACorneredButton();

public:	

	void Interact() override;

		FPressHappenedDelegate PressHappened;

private:

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> PressAudio;
};
