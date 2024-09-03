// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "System/CorneredInitializable.h"
#include "BeltElement.generated.h"

class ABeltController;
class UConfig_IngredientGeneration;

UCLASS()
class CORNERED_API ABeltElement : public AActor, public ICorneredInitializable
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

	void InitializeHappened() override;

private:

	UFUNCTION()
	void ActivateHappened();
};
