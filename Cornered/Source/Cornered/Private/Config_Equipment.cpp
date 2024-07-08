// Fill out your copyright notice in the Description page of Project Settings.


#include "Config_Equipment.h"
#include "CharacterWeapon.h"
#include "Product.h"

TSubclassOf<AActor> UConfig_Equipment::GetEquippedProduct(EItemType itemType) const {

    TSubclassOf<AActor> result = nullptr;
    
    for (int i = 0; i < EquippedProductEntries.Num(); i++) {
        if (EquippedProductEntries[i].Key == itemType) {
            result = EquippedProductEntries[i].Value;
            return result;
        }
    }

    return result;
}



FWeaponSettingsEntry UConfig_Equipment::GetWeaponSettings(EItemType itemType) const {
    for (int i = 0; i < WeaponSettingsEntries.Num(); i++) {
        if (WeaponSettingsEntries[i].Key == itemType) {
            return WeaponSettingsEntries[i];
        }
    }

    return FWeaponSettingsEntry();
}

FShieldSettingsEntry UConfig_Equipment::GetShieldSettings(EItemType itemType) const {
    for (int i = 0; i < ShieldSettingsEntries.Num(); i++) {
        if (ShieldSettingsEntries[i].Key == itemType) {
            return ShieldSettingsEntries[i];
        }
    }

    return FShieldSettingsEntry();
}

FAdditionalSettingsEntry UConfig_Equipment::GetAdditionalSettings(EItemType itemType) const {
    for (int i = 0; i < AdditionalSettingsEntries.Num(); i++) {
        if (AdditionalSettingsEntries[i].Key == itemType) {
            return AdditionalSettingsEntries[i];
        }
    }

    return FAdditionalSettingsEntry();
}