// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CorneredCharacter.h"
#include "Config_Equipment.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;
class AEnemyController;
class AController;
class UExternalEquipper;
class UStateTreeComponent;
class UConfig_AI;
class UHideSpotFinder;
class UCharacterAnimInstance;

UCLASS()
class CORNERED_API AEnemyCharacter : public ACorneredCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TObjectPtr<UHideSpotFinder> HideSpotFinderComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UExternalEquipper> ExternalEquipperComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPawnSensingComponent> PawnSensingComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UStateTreeComponent> StateTreeComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_AI> AIConfig;

public:
	AEnemyCharacter();

	void SetEquipment(FItemDatas weapon, FItemDatas shield, FItemDatas additional);

protected:

	virtual IMovableCharacter* GetOwnedController() const override;

	virtual UCharacterAnimInstance* GetOwnedAnimInstance() const override;
};
