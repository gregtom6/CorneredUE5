// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Config_Controls.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FControlsPageDatas
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TObjectPtr<UTexture2D> ImageOfGameInteraction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        TObjectPtr<UTexture2D> ImageOfControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dictionary Entry")
        FString Text;

};

/**
 * 
 */
UCLASS()
class CORNERED_API UConfig_Controls : public UDataAsset
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere)
        TArray<FControlsPageDatas> ControlsPageDatas;

    UFUNCTION()
        FControlsPageDatas GetControlsPageDatas(int32 index);

    UFUNCTION()
        int32 GetControlsPageCount();

};
