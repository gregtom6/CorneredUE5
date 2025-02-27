// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DataAssets/Config_Equipment.h"
#include "Characters/ActorComponents/CharacterWeapon.h"
#include "Items/Product.h"

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

FItemData UConfig_Equipment::GetRandomWeapon() const {
    int index = FMath::RandRange(0, Weapons.Num() - 1);
    return Weapons[index];
}

FItemData UConfig_Equipment::GetRandomShield() const {
    int index = FMath::RandRange(0, Shields.Num() - 1);
    return Shields[index];
}

FItemData UConfig_Equipment::GetRandomAdditional() const {
    int index = FMath::RandRange(0, Additionals.Num() - 1);
    return Additionals[index];
}