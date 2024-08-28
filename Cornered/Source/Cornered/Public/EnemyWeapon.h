// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWeapon.h"
#include "EnemyWeapon.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UEnemyWeapon : public UCharacterWeapon
{
	GENERATED_BODY()

public:

	UEnemyWeapon();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	virtual ECollisionChannel GetOpponentTraceChannel() const override;
};
