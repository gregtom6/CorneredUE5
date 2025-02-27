// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/ProgressionGameState.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Configs/DataAssets/Config_Progress.h"
#include "Characters/Systems/CorneredCharacter.h"
#include "System/CorneredGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "Characters/Systems/PlayerCharacter.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Characters/Systems/CharacterSpawner.h"

void AProgressionGameState::OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter) {

	if (DefeatedCharacter->IsA<AEnemyCharacter>()) {
		StepUnlockLevel();
	}
	else {
		ResetUnlockLevel();
	}

	CharacterDefeated.Broadcast(DefeatedCharacter);
}

void AProgressionGameState::OnCharacterShotReceived(ACorneredCharacter* CharacterReceivedShot) {
	CharacterShotReceived.Broadcast(CharacterReceivedShot);
}

void AProgressionGameState::OnSoulSniffed() {
	
	SoulSniffedCount += 1;

	SaveProgress();
}

void AProgressionGameState::BeginPlay()
{
	Super::BeginPlay();

	ResetProgress();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);
	SubscribeToCharacterDamageDelegates(PlayerCharacter);

	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->OnEnemyGenerated.AddUniqueDynamic(this, &AProgressionGameState::OnEnemyGenerated);
		MySubsystem->OnSoulDissipated.AddUniqueDynamic(this, &AProgressionGameState::OnSoulSniffed);
	}
}

void AProgressionGameState::OnEnemyGenerated(AEnemyCharacter* EnemyCharacter) {

	SubscribeToCharacterDamageDelegates(EnemyCharacter);
}

void AProgressionGameState::SubscribeToCharacterDamageDelegates(ACorneredCharacter* Character) {
	if (Character) {
		UCharacterHealth* Health = Character->CharacterHealth;
		if (Health) {
			Health->CharacterShotReceived.AddUniqueDynamic(this, &AProgressionGameState::OnCharacterShotReceived);
			Health->CharacterDefeated.AddUniqueDynamic(this, &AProgressionGameState::OnCharacterDefeated);
		}
	}
}

void AProgressionGameState::ResetProgress() {
	
	UnlockLevel = 0;
	SoulSniffedCount = 0;

	SaveProgress();
}

void AProgressionGameState::ResetUnlockLevel() {
	UnlockLevel = 0;

	SaveProgress();
}

void AProgressionGameState::StepUnlockLevel() {

	UnlockLevel = FMath::Clamp(UnlockLevel + 1, 0, ProgressConfig->GetMaxUnlockLevel());

	SaveProgress();
}

void AProgressionGameState::SaveProgress() {
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	UGameInstance* GameInstance = GameMode->GetGameInstance();

	UCorneredGameInstance* CorneredGameInstance = Cast<UCorneredGameInstance>(GameInstance);

	CorneredGameInstance->SaveUnlockLevel(UnlockLevel);

	CorneredGameInstance->SaveSniffedSoulCount(SoulSniffedCount);
}

bool AProgressionGameState::IsAbilityAlreadyUnlocked(EAbility Ability) {

    return ProgressConfig->IsAbilityUnlocked(Ability, this);
}

int32 AProgressionGameState::GetCurrentSniffedSoulCount() const {
	return SoulSniffedCount;
}

int32 AProgressionGameState::GetCurrentOverloadSoulCount() const {
	int32 overloadSouls = SoulSniffedCount - ProgressConfig->GetSoulBorderCount(GetWorld());
	if (overloadSouls > 0) {
		return overloadSouls;
	}

	return 0;
}