// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ActorComponents/CharacterWeapon.h"
#include "EnemyWeapon.generated.h"

class UConfig_AI;

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UEnemyWeapon : public UCharacterWeapon
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_AI> AIConfig;

public:

	UEnemyWeapon();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	virtual ECollisionChannel GetOpponentTraceChannel() const override;
};
