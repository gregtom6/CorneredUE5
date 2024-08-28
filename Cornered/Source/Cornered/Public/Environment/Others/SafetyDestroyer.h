// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SafetyDestroyer.generated.h"

/**
 *
 */
UCLASS()
class CORNERED_API ASafetyDestroyer : public ATriggerBox
{
	GENERATED_BODY()

public:
	ASafetyDestroyer();

private:

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
};
