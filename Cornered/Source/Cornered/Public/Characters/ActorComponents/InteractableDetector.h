// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractableDetector.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UInteractableDetector : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TObjectPtr<UWorld> CachedWorld;

	bool bIsValidHit;

	FHitResult HitResult;
public:
	// Sets default values for this component's properties
	UInteractableDetector();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool ItWasValidHit() const;

	FHitResult GetHitResult() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
