// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPickable.h"
#include "Equippable.h"
#include "CharacterWeapon.h"
#include "MixingItemDetector.h"
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

	void Pickup(AActor* Actor) override;

	void Drop() override;

	bool IsPicked() const override;

	bool WasPickedAnytime() const override;

	virtual IEquippable* GetEquippable() const;

	UFUNCTION()
		void SetState(EItemState state);

	UPROPERTY(EditAnywhere)
		EItemType ItemType;
		EItemState ItemState;

	UFUNCTION()
		EItemType GetItemType() const;

	UFUNCTION()
		EItemState GetItemState() const;
};
