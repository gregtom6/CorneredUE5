// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWeapon.h"
#include "PlayerWeapon.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UPlayerWeapon : public UCharacterWeapon
{
	GENERATED_BODY()

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void ShootHappened();

	virtual ECollisionChannel GetOpponentTraceChannel() const override;
};
