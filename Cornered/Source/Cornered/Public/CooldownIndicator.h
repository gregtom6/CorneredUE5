// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CooldownIndicator.generated.h"

class UCharacterWeapon;
class UPaperSpriteComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UCooldownIndicator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCooldownIndicator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void SetComponents(USceneComponent* parent, UCharacterWeapon* weapon);

	UPROPERTY(VisibleAnywhere)
		USceneComponent* CooldownIndicatorParentComp;

	UPROPERTY(VisibleAnywhere)
		UCharacterWeapon* CharacterWeapon;

	UPROPERTY(VisibleAnywhere)
		UPaperSpriteComponent* CooldownIndicatorPaperSprite;
};
