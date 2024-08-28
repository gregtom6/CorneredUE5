// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/EnemyHealth.h"
#include "Configs/DataAssets/Config_Character_General.h"

float UEnemyHealth::GetMaxHealth() const {
	return CharacterConfig->EnemyMaxHealth;
}

float UEnemyHealth::GetReloadWaitingMaxTime() const {
	return CharacterConfig->EnemyWaitUntilHealthReloadStarts;
}