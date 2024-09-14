#include "Characters/StateTreeConditions/ShootPositionEnemyCondition.h"
#include "Characters/Systems/PlayerCharacter.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include <Kismet/GameplayStatics.h>

bool FShootPositionEnemyCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	// Retrieve instance data from the context
	const FStateTreeShootConditionData* InstanceData = Context.GetInstanceDataPtr<FStateTreeShootConditionData>(*this);

	// Check if instance data is valid
	if (!InstanceData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Instance data or Source is missing"));
		return false;
	}

	if (InstanceData->EnemyCurrentHealth <= 0.f) {
		return false;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(Context.GetWorld(), 0);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerPawn);

	if (PlayerCharacter) {
		UCharacterHealth* Health = PlayerCharacter->CharacterHealth;
		if (Health && Health->GetCurrentHealth() <= 0.f) {
			return false;
		}
	}

	return (InstanceData->EnemyCurrentHealth / InstanceData->EnemyMaxHealth) * 100.f >= InstanceData->AttackWhenLifeMoreThanPercentage && InstanceData->bIsReadyToShoot;
}