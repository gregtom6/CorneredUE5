// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UUserWidget;
class UAudioComponent;
/**
 * 
 */
UCLASS()
class CORNERED_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AMainMenuHUD();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UUserWidget> UserWidgetClass;

private:

	UPROPERTY()
	UUserWidget* UserWidgetInstance;

	UPROPERTY(EditAnywhere)
		UAudioComponent* MainMenuBGMComp;

	UPROPERTY(EditAnywhere)
		UAudioComponent* SFXComp;

	UFUNCTION()
		void UIPressHappened();
};
