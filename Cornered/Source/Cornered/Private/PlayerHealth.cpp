// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "PlayerHealth.h"
#include "Config_Character_General.h"

float UPlayerHealth::GetMaxHealth() {
	return CharacterConfig->MaxHealth;
}

float UPlayerHealth::GetReloadWaitingMaxTime() {
	return CharacterConfig->WaitUntilHealthReloadStarts;
}