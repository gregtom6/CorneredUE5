// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/ItemData.h"
#include "Environment/MixingMachine/MixingItemDetector.h"
#include "Config_Equipment.generated.h"

class AProduct;
class UMaterialInterface;
class UNiagaraSystem;

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
		: Key(EItemType::Count), DecalSize(1.f,1.f,1.f), DecalLifeSpan(0.f), CooldownTimeInSec(0.f), Damage(0.f) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	EItemType Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TArray<TObjectPtr<UMaterialInterface>> DecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	TObjectPtr<UNiagaraSystem> NiagaraDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	FVector DecalSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float DecalLifeSpan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float CooldownTimeInSec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
	float Damage;

	UMaterialInterface* GetRandomDecal() const
	{
		return DecalMaterial[FMath::RandRange(0, DecalMaterial.Num()-1)];
	}

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
	TArray<FItemData> Weapons;
	UPROPERTY(EditAnywhere)
	TArray<FItemData> Shields;
	UPROPERTY(EditAnywhere)
	TArray<FItemData> Additionals;

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

	FItemData GetRandomWeapon() const;

	FItemData GetRandomShield() const;

	FItemData GetRandomAdditional() const;
};
