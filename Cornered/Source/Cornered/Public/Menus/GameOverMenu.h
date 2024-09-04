// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menus/MainMenu.h"
#include "GameOverMenu.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class CORNERED_API UGameOverMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	FUIPressHappenedDelegate UIPressHappened;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> GameLevel;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenuLevel;
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
