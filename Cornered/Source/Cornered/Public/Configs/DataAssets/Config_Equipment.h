// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/ItemType.h"
#include "Environment/MixingMachine/MixingItemDetector.h"
#include "Config_Equipment.generated.h"

class AProduct;
class UMaterialInterface;

USTRUCT(BlueprintType)
struct FItemDatas
{
	GENERATED_BODY()

	FItemDatas()
		: Key(EItemType::Count),
		Value(EItemState::Count) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemState Value;
};


USTRUCT(BlueprintType)
struct FEquippedProductEntry
{
	GENERATED_BODY()

	FEquippedProductEntry()
		: Key(EItemType::Count) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TSubclassOf<AActor> Value;
};

USTRUCT(BlueprintType)
struct FWeaponSettingsEntry
{
	GENERATED_BODY()

	FWeaponSettingsEntry()
		: Key(EItemType::Count), CooldownTimeInSec(0.f), Damage(0.f) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TObjectPtr<UMaterialInterface> DecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	FVector DecalSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float DecalLifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float CooldownTimeInSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float Damage;

};

USTRUCT(BlueprintType)
struct FShieldSettingsEntry
{
	GENERATED_BODY()

	FShieldSettingsEntry()
		: Key(EItemType::Count), DamageDivider(0.f) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float DamageDivider;

};

USTRUCT(BlueprintType)
struct FAdditionalSettingsEntry
{
	GENERATED_BODY()

	FAdditionalSettingsEntry()
		: Key(EItemType::Count), Multiplier(0.f) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float Multiplier;

};

UCLASS()
class CORNERED_API UConfig_Equipment : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float EquipTimeInSeconds;

	UPROPERTY(EditAnywhere)
	float PercentageOfEquipPath;

private:

	UPROPERTY(EditAnywhere)
	TArray<FItemDatas> Weapons;
	UPROPERTY(EditAnywhere)
	TArray<FItemDatas> Shields;
	UPROPERTY(EditAnywhere)
	TArray<FItemDatas> Additionals;

	UPROPERTY(EditAnywhere, Category = "Dictionary")
	TArray<FEquippedProductEntry> EquippedProductEntries;

	UPROPERTY(EditAnywhere, Category = "Dictionary")
	TArray<FWeaponSettingsEntry> WeaponSettingsEntries;

	UPROPERTY(EditAnywhere, Category = "Dictionary")
	TArray<FShieldSettingsEntry> ShieldSettingsEntries;

	UPROPERTY(EditAnywhere, Category = "Dictionary")
	TArray<FAdditionalSettingsEntry> AdditionalSettingsEntries;

public:

	TSubclassOf<AActor> GetEquippedProduct(EItemType itemType) const;

	FWeaponSettingsEntry GetWeaponSettings(EItemType itemType) const;

	FShieldSettingsEntry GetShieldSettings(EItemType itemType) const;

	FAdditionalSettingsEntry GetAdditionalSettings(EItemType itemType) const;

	FItemDatas GetRandomWeapon() const;

	FItemDatas GetRandomShield() const;

	FItemDatas GetRandomAdditional() const;
};
