// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "CorneredCheats.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UCorneredCheats : public UCheatManager
{
	GENERATED_BODY()

public:

	UCorneredCheats();

	UFUNCTION(exec)
	void ManageAIDebugDrawings();
	UFUNCTION(exec)
	void ManageAIHideSpotDrawings(TArray<AActor*> FoundActors);
	UFUNCTION(exec)
	void ManageEnemyWeaponDebugDrawings(TArray<AActor*> FoundActors);

	void RegisterCommands();

private:

	bool bEnabled;
};
