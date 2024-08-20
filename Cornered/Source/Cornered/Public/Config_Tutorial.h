// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

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
        TObjectPtr<UTexture2D> Image;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        FString Text;

};

UCLASS()
class CORNERED_API UConfig_Tutorial : public UDataAsset
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere)
        TArray<FTutorialPageDatas> TutorialPageDatas;

public:

    UFUNCTION()
        FTutorialPageDatas GetTutorialPageDatas(int32 index) const;

    UFUNCTION()
        int32 GetTutorialPageCount() const;
};
