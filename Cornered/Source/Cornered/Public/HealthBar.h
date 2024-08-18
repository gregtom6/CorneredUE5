// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;

UCLASS()
class CORNERED_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    UPROPERTY(meta = (BindWidget))
        TObjectPtr<UProgressBar> Health;
};
