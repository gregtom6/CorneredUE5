// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Tutorial.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FTutorialPageDatas
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        UTexture2D* Image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        FString Text;

};

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Tutorial : public UDataAsset
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere)
        TArray<FTutorialPageDatas> TutorialPageDatas;

    UFUNCTION()
        FTutorialPageDatas GetTutorialPageDatas(int32 index);

    UFUNCTION()
        int32 GetTutorialPageCount();
};
