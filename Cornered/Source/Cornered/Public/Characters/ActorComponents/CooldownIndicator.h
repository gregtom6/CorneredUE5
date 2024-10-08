// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CooldownIndicator.generated.h"

class UCharacterWeapon;
class UPaperSpriteComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UCooldownIndicator : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> CooldownIndicatorParentComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCharacterWeapon> CharacterWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperSpriteComponent> CooldownIndicatorPaperSprite;

public:
	UCooldownIndicator();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetComponents(USceneComponent* parent, UCharacterWeapon* weapon);

};
