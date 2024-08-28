// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Menus/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "Characters/ActorComponents/CharacterHealth.h"

void UHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (Health)
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(PlayerController->GetPawn());
        UCharacterHealth* CharHealth = PlayerPawn->FindComponentByClass<UCharacterHealth>();

        Health->SetPercent(CharHealth->GetCurrentHealth()/100.f); // Example: Set progress to 50%
    }
}