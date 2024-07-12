// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownIndicator.h"
#include "PlayerWeapon.h"
#include "PaperSpriteComponent.h"

// Sets default values for this component's properties
UCooldownIndicator::UCooldownIndicator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCooldownIndicator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCooldownIndicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CharacterWeapon->IsThereEquippedWeapon())
	{
		return;
	}

	float percentage = CharacterWeapon->GetCooldownTimeLeftPercentageBetween01();

	CooldownIndicatorParentComp->SetRelativeScale3D(FVector(CooldownIndicatorParentComp->GetRelativeScale3D().X, CooldownIndicatorParentComp->GetRelativeScale3D().Y, percentage));

	CooldownIndicatorPaperSprite->SetSpriteColor(percentage >= 1.0f ? FLinearColor::Green : FLinearColor::Red);

}

void UCooldownIndicator::SetComponents(USceneComponent* parent, UPlayerWeapon* weapon) {
	CooldownIndicatorParentComp = parent;
	CharacterWeapon = weapon;

	CooldownIndicatorPaperSprite = Cast<UPaperSpriteComponent>(parent);
}