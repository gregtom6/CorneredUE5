// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Configs/DeveloperSettings/ConfigEquipmentDevSettings.h"

FItemDatas UConfigEquipmentDevSettings::GetWeapon() const {
    if (bShouldUseFixWeapon) {
        return GetFixWeapon();
    }
    return GetRandomWeapon();
}

FItemDatas UConfigEquipmentDevSettings::GetRandomWeapon() const {
    int index = FMath::RandRange(0, Weapons.Num() - 1);
    return Weapons[index];
}

FItemDatas UConfigEquipmentDevSettings::GetFixWeapon() const {
    for (int i = 0; i < Weapons.Num(); i++) {
        if (Weapons[i].Key == FixWeapon) {
            return Weapons[i];
        }
    }

    return GetRandomWeapon();
}

FItemDatas UConfigEquipmentDevSettings::GetRandomShield() const {
    int index = FMath::RandRange(0, Shields.Num() - 1);
    return Shields[index];
}

FItemDatas UConfigEquipmentDevSettings::GetRandomAdditional() const {
    int index = FMath::RandRange(0, Additionals.Num() - 1);
    return Additionals[index];
}