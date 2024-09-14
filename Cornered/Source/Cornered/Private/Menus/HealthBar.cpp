// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Menus/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Configs/DataAssets/Config_Time.h"
#include "Configs/DataAssets/Config_Visual.h"
#include "System/ProgressionGameState.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "Characters/Systems/EnemyCharacter.h"

void UHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	DeltaHealth->SetPercent(Health->GetPercent());
	PreviousHealthPercent = Health->GetPercent();

	AGameStateBase* State = GetWorld()->GetGameState();
	AProgressionGameState* ProgressionGameState = Cast<AProgressionGameState>(State);

	ProgressionGameState->CharacterShotReceived.AddUniqueDynamic(this, &UHealthBar::OnCharacterShotReceived);
}

void UHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Health)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(PlayerController->GetPawn());
		UCharacterHealth* CharHealth = PlayerPawn->FindComponentByClass<UCharacterHealth>();

		float currentHealthPercent = CharHealth->GetCurrentHealth() / 100.f;

		Health->SetPercent(currentHealthPercent);

		PreviousHealthPercent = currentHealthPercent;
	}
}

void UHealthBar::OnCharacterShotReceived(ACorneredCharacter* Character) {
	if (Character->IsA<AEnemyCharacter>()) {
		return;
	}

	DeltaHealth->SetPercent(PreviousHealthPercent);
}