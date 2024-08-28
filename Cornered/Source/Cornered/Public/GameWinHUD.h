// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameWinHUD.generated.h"

class UUserWidget;
class UAudioComponent;

UCLASS()
class CORNERED_API AGameWinHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UUserWidget> UserWidgetClass;

private:

	UPROPERTY()
		TObjectPtr<UUserWidget> UserWidgetInstance;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> GameWinBGMComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> SFXComp;

public:

	AGameWinHUD();

	virtual void BeginPlay() override;


private:

	UFUNCTION()
		void UIPressHappened();
};
