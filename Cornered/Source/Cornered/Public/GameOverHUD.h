// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameOverHUD.generated.h"

class UUserWidget;
class UAudioComponent;

/**
 * 
 */
UCLASS()
class CORNERED_API AGameOverHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AGameOverHUD();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UUserWidget> UserWidgetClass;

private:

	UPROPERTY()
		TObjectPtr<UUserWidget> UserWidgetInstance;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> GameOverBGMComp;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UAudioComponent> SFXComp;

	UFUNCTION()
		void UIPressHappened();
};
