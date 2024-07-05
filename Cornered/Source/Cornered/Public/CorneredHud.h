// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CorneredHud.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class CORNERED_API ACorneredHud : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TArray<TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
		TArray<UUserWidget*> WidgetInstances;
};
