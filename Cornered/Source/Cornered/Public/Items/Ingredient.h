// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/IPickable.h"
#include "Items/Equippable.h"
#include "Characters/ActorComponents/CharacterWeapon.h"
#include "Environment/MixingMachine/MixingItemDetector.h"
#include "Ingredient.generated.h"

class UStaticMeshComponent;

UCLASS()
class CORNERED_API AIngredient : public AActor, public IIPickable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EItemType ItemType;
	EItemState ItemState;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

private:

	bool bWasPickedAnyTime;

public:
	// Sets default values for this actor's properties
	AIngredient();

	void Pickup(AActor* Actor) override;

	void Drop() override;

	bool IsPicked() const override;

	bool WasPickedAnytime() const override;

	virtual IEquippable* GetEquippable() const;

	void SetState(EItemState state);

	UFUNCTION(BlueprintPure)
	EItemType GetItemType() const;

	UFUNCTION(BlueprintPure)
	EItemState GetItemState() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
