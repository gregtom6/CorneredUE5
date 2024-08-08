// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameWinHUD.generated.h"

class UUserWidget;
class UAudioComponent;
/**
 * 
 */
UCLASS()
class CORNERED_API AGameWinHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AGameWinHUD();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UUserWidget> UserWidgetClass;

private:

	UPROPERTY()
		UUserWidget* UserWidgetInstance;

	UPROPERTY(EditAnywhere)
		UAudioComponent* GameWinBGMComp;

	UPROPERTY(EditAnywhere)
		UAudioComponent* SFXComp;

	UFUNCTION()
		void UIPressHappened();
};
