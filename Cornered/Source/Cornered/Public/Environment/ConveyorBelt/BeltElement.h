// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeltElement.generated.h"

class ABeltController;
class UConfig_IngredientGeneration;

UCLASS()
class CORNERED_API ABeltElement : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> ItemPivot;

	UPROPERTY()
		TObjectPtr<ABeltController> BeltController;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UConfig_IngredientGeneration> IngredientGenConfig;

	FTimerHandle TimerHandle;

	FVector ItemPivotLocation;

public:
	ABeltElement();

	virtual void Tick(float DeltaTime) override;

	void SetBeltController(ABeltController* controller);

	virtual void SetActorHiddenInGame(bool bNewHidden) override;

private:

	void TimerFunction();
};
