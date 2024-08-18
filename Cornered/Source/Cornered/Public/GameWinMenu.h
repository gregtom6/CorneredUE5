// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"
#include "GameWinMenu.generated.h"


class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CORNERED_API UGameWinMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

		FUIPressHappenedDelegate UIPressHappened;

protected:

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> Restart;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> Quit;

	UFUNCTION()
		void RestartOnClick();

	UFUNCTION()
		void QuitOnClick();
};
