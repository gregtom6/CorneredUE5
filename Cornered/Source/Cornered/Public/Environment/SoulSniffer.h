// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulSniffer.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UActorSequenceComponent;
class UAudioComponent;
class UTextRenderComponent;
class UBoxComponent;
class UConfig_SoulSniffer;

UENUM(BlueprintType)
enum class ESoulSnifferState :uint8
{
	Disabled,
	WaitBeforeCatch,
	Catch,
	WaitBeforeProcessing,
	Processing,
	WaitAfterProcessing,
	Processed,

	Count,
};

UCLASS()
class CORNERED_API ASoulSniffer : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> CatchSequenceComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> ProcessingSequenceComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UActorSequenceComponent> ProcessedSequenceComp;
	

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_SoulSniffer> SnifferConfig;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Led1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Led2;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProcessingLed;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Target;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DissipateTarget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> CatchAudioComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> ProcessingAudioComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAudioComponent> ProcessedAudioComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextRenderComponent> CurrentCountTextComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextRenderComponent> SlashTextComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextRenderComponent> BorderCountTextComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> SoulDetector;

	ESoulSnifferState State = ESoulSnifferState::Disabled;

	FTimerHandle TimerHandle;
	
public:	
	// Sets default values for this actor's properties
	ASoulSniffer();

	FVector GetTargetLocation();

	FVector GetDissipateTargetLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnEnterDetectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void SoulCatched();

	void SoulProcessing();

	void StopSoulProcessing();

	void SoulProcessed();

	void SetBackDefaultState();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
