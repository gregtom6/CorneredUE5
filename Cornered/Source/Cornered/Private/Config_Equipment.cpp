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