// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPickable.h"
#include "Equippable.h"
#include "Ingredient.generated.h"

class UStaticMeshComponent;

UCLASS()
class CORNERED_API AIngredient : public AActor, public IIPickable
{
	GENERATED_BODY()

private:

	bool bWasPickedAnyTime;
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Pickup(AActor* Actor) override;

	void Drop() override;

	bool IsPicked() const override;

	bool WasPickedAnytime() const override;

	virtual IEquippable* GetEquippable() const;
};
