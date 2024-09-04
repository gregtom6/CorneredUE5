// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UPanelWidget;
class UConfig_Tutorial;
class UConfig_Controls;
class UImage;
class UTextBlock;

UENUM(BlueprintType)
enum class EMainMenuState : uint8
{
	Main,
	Hint,
	Controls,

	Count,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIPressHappenedDelegate);

UCLASS()
class CORNERED_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	FUIPressHappenedDelegate UIPressHappened;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NewGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Hint;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Controls;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Quit;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FromTutorialToMainMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TutorialLeftPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TutorialRightPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FromControlsToMainMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ControlsLeftPage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ControlsRightPage;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Tutorial> TutorialConfig;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Controls> ControlsConfig;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> TutorialImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ControlsLeftImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ControlsRightImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ControlsText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TutorialText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> MainMenuParent;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> TutorialParent;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> ControlsParent;

	EMainMenuState MainMenuState;

	int32 CurrentPageIndex;
public:
	virtual void NativeConstruct() override;
protected:
	UFUNCTION()
	void NewGameOnClick();

	UFUNCTION()
	void HintOnClick();

	UFUNCTION()
	void ControlsOnClick();

	UFUNCTION()
	void QuitOnClick();

	UFUNCTION()
	void FromTutorialToMainMenuOnClick();

	UFUNCTION()
	void TutorialLeftPageOnClick();

	UFUNCTION()
	void TutorialRightPageOnClick();

	UFUNCTION()
	void FromControlsToMainMenuOnClick();

	UFUNCTION()
	void ControlsLeftPageOnClick();

	UFUNCTION()
	void ControlsRightPageOnClick();
private:
	void ShowState();

	void SetMainMenuState(EMainMenuState state);

	void BackToMain();

	void ShowCurrentControlsPage();

	void ShowCurrentTutorialPage();

	void ManageTutorialPageSteppingButtons();

	void ManageControlsPageSteppingButtons();
};
