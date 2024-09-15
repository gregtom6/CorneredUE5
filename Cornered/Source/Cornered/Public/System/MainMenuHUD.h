// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UUserWidget;
class UAudioComponent;

UCLASS()
class CORNERED_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> UserWidgetClass;

private:

	UPROPERTY()
	TObjectPtr<UUserWidget> UserWidgetInstance;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> MainMenuBGMComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> SFXComp;

public:

	AMainMenuHUD();

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void UIPressHappened();

};
