// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GateController.generated.h"

class USceneComponent;
class UBoxComponent;
class UActorSequenceComponent;
class UActorSequencePlayer;

UCLASS()
class CORNERED_API AGateController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGateController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> GateVisualsParentComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> EnterDetectorParentComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> ExitDetectorParentComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UBoxComponent> EnterDetectorComp;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UBoxComponent> ExitDetectorComp;

	UFUNCTION()
		void OnEnterDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnExitDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
		UActorSequenceComponent* OpenSequ;
	UPROPERTY()
		UActorSequenceComponent* CloseSequ;
};