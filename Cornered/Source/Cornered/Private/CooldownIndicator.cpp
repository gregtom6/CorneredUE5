// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CooldownIndicator.h"
#include "CharacterWeapon.h"
#include "PaperSpriteComponent.h"

UCooldownIndicator::UCooldownIndicator()
{
	PrimaryComponentTick.bCanEverTick = true;
}

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

void UCooldownIndicator::SetComponents(USceneComponent* parent, UCharacterWeapon* weapon) {
	CooldownIndicatorParentComp = parent;
	CharacterWeapon = weapon;

	CooldownIndicatorPaperSprite = Cast<UPaperSpriteComponent>(parent);
}