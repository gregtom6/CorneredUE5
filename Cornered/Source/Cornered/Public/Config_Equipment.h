// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterWeapon.h"
#include "Config_Equipment.generated.h"

class AProduct;

USTRUCT(BlueprintType)
struct FEquippedProductEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TSubclassOf<AActor> Value;
};

USTRUCT(BlueprintType)
struct FWeaponSettingsEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        float CooldownTimeInSec;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        float Damage;

};

USTRUCT(BlueprintType)
struct FShieldSettingsEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        float DamageDivider;

};

USTRUCT(BlueprintType)
struct FAdditionalSettingsEntry
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        EItemType Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        float Multiplier;

};

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Equipment : public UDataAsset
{
	GENERATED_BODY()
	
private:

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FEquippedProductEntry> EquippedProductEntries;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FWeaponSettingsEntry> WeaponSettingsEntries;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FShieldSettingsEntry> ShieldSettingsEntries;

    UPROPERTY(EditAnywhere, Category = "Dictionary")
        TArray<FAdditionalSettingsEntry> AdditionalSettingsEntries;

public:

    UFUNCTION()
        TSubclassOf<AActor> GetEquippedProduct(EItemType itemType) const;

    UFUNCTION()
        FWeaponSettingsEntry GetWeaponSettings(EItemType itemType) const;

    UFUNCTION()
        FShieldSettingsEntry GetShieldSettings(EItemType itemType) const;

    UFUNCTION()
        FAdditionalSettingsEntry GetAdditionalSettings(EItemType itemType) const;
};
