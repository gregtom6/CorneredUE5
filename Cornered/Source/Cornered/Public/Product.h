// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "Product.generated.h"

/**
 *
 */
UCLASS()
class CORNERED_API AProduct : public AIngredient, public IEquippable
{
	GENERATED_BODY()

		UFUNCTION()
		// Inherited via IEquippable
		virtual void Equip() override;

		virtual IEquippable* GetEquippable() const override;
};
