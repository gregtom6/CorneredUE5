// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DeveloperSettings/ConfigEquipmentDevSettings.h"

FItemData UConfigEquipmentDevSettings::GetWeapon() const {
    if (bShouldUseFixWeapon) {
        return GetFixWeapon();
    }
    return GetRandomWeapon();
}

FItemData UConfigEquipmentDevSettings::GetRandomWeapon() const {
    int index = FMath::RandRange(0, Weapons.Num() - 1);
    return Weapons[index];
}

FItemData UConfigEquipmentDevSettings::GetFixWeapon() const {
    for (int i = 0; i < Weapons.Num(); i++) {
        if (Weapons[i].ItemType == FixWeapon) {
            return Weapons[i];
        }
    }

    return GetRandomWeapon();
}

FItemData UConfigEquipmentDevSettings::GetRandomShield() const {
    int index = FMath::RandRange(0, Shields.Num() - 1);
    return Shields[index];
}

FItemData UConfigEquipmentDevSettings::GetRandomAdditional() const {
    int index = FMath::RandRange(0, Additionals.Num() - 1);
    return Additionals[index];
}