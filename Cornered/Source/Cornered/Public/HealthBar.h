// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class CORNERED_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
    UPROPERTY(meta = (BindWidget))
        TObjectPtr<UProgressBar> Health;
};
