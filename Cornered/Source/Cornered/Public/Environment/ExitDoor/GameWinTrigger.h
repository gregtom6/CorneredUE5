// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameWinTrigger.generated.h"

/**
 *
 */
UCLASS()
class CORNERED_API AGameWinTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:

	AGameWinTrigger();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
