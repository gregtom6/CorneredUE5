// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquippedWeapon.generated.h"

class USceneComponent;
class UPointLightComponent;
class UActorSequenceComponent;
class UActorSequencePlayer;

UCLASS()
class CORNERED_API AEquippedWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquippedWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<USceneComponent> MuzzlePosition;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UPointLightComponent> PointLightComp;
	UPROPERTY()
		UActorSequenceComponent* ShotSequ;

	UFUNCTION()
		void ShotHappened();
};
