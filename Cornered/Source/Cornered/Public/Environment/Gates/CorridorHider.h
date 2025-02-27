// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorridorHider.generated.h"

class ACorneredCharacter;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class CORNERED_API ACorridorHider : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallLeftComp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> WallRightComp;

public:	
	// Sets default values for this actor's properties
	ACorridorHider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTimerOverHappened();

private:

	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);

	void ManageMeshes(bool bActivate);
};
