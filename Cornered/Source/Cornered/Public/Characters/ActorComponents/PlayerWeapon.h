// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ActorComponents/CharacterWeapon.h"
#include "PlayerWeapon.generated.h"

class UInteractableDetector;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UPlayerWeapon : public UCharacterWeapon
{
	GENERATED_BODY()

private:

	TObjectPtr<UInteractableDetector> InteractableDetectorComp;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual FShotRayDatas GetShotRayDatas() const override;

private:

	UFUNCTION()
	void ShootHappened();

	virtual ECollisionChannel GetOpponentTraceChannel() const override;
};
