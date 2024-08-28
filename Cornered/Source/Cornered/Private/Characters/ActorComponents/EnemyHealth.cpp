// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyHealth.h"
#include "Config_Character_General.h"

float UEnemyHealth::GetMaxHealth() const {
	return CharacterConfig->EnemyMaxHealth;
}

float UEnemyHealth::GetReloadWaitingMaxTime() const {
	return CharacterConfig->EnemyWaitUntilHealthReloadStarts;
}