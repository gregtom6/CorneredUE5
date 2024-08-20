// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"
#include "GameWinMenu.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class CORNERED_API UGameWinMenu : public UUserWidget
{
	GENERATED_BODY()

public:
		FUIPressHappenedDelegate UIPressHappened;

protected:

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> Restart;

	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UButton> Quit;
	
public:
	virtual void NativeConstruct() override;

protected:

	UFUNCTION()
		void RestartOnClick();

	UFUNCTION()
		void QuitOnClick();
};
