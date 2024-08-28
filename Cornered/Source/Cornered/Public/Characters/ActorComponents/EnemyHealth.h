// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterHealth.h"
#include "EnemyHealth.generated.h"

/**
 *
 */
UCLASS()
class CORNERED_API UEnemyHealth : public UCharacterHealth
{
	GENERATED_BODY()

public:

	virtual float GetMaxHealth() const override;
protected:

	virtual float GetReloadWaitingMaxTime() const override;
};
