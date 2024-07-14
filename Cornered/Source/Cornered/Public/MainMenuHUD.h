// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class CORNERED_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UUserWidget> UserWidgetClass;

private:

	UPROPERTY()
	UUserWidget* UserWidgetInstance;
};
