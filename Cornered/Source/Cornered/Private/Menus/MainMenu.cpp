// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Menus/MainMenu.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Configs/DataAssets/Config_Controls.h"
#include "Configs/DataAssets/Config_Tutorial.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "System/LevelManager.h"
#include "Configs/DeveloperSettings/ConfigLevelsDevSettings.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	MainMenuState = EMainMenuState::Main;

	CurrentPageIndex = 0;

	ShowState();

	if (NewGame)
	{
		NewGame->OnClicked.AddDynamic(this, &UMainMenu::NewGameOnClick);
	}

	if (Hint)
	{
		Hint->OnClicked.AddDynamic(this, &UMainMenu::HintOnClick);
	}

	if (Controls)
	{
		Controls->OnClicked.AddDynamic(this, &UMainMenu::ControlsOnClick);
	}

	if (Quit)
	{
		Quit->OnClicked.AddDynamic(this, &UMainMenu::QuitOnClick);
	}

	if (FromTutorialToMainMenu)
	{
		FromTutorialToMainMenu->OnClicked.AddDynamic(this, &UMainMenu::FromTutorialToMainMenuOnClick);
	}

	if (TutorialLeftPage)
	{
		TutorialLeftPage->OnClicked.AddDynamic(this, &UMainMenu::TutorialLeftPageOnClick);
	}

	if (TutorialRightPage)
	{
		TutorialRightPage->OnClicked.AddDynamic(this, &UMainMenu::TutorialRightPageOnClick);
	}

	if (FromControlsToMainMenu)
	{
		FromControlsToMainMenu->OnClicked.AddDynamic(this, &UMainMenu::FromControlsToMainMenuOnClick);
	}

	if (ControlsLeftPage)
	{
		ControlsLeftPage->OnClicked.AddDynamic(this, &UMainMenu::ControlsLeftPageOnClick);
	}

	if (ControlsRightPage)
	{
		ControlsRightPage->OnClicked.AddDynamic(this, &UMainMenu::ControlsRightPageOnClick);
	}
}

void UMainMenu::SetMainMenuState(EMainMenuState state) {
	MainMenuState = state;
	ShowState();
}

void UMainMenu::ShowCurrentControlsPage() {
	ManageControlsPageSteppingButtons();

	FControlsPageDatas pageDatas = ControlsConfig->GetControlsPageDatas(CurrentPageIndex);
	ControlsLeftImage->SetBrushFromTexture(pageDatas.ImageOfGameInteraction);
	ControlsRightImage->SetBrushFromTexture(pageDatas.ImageOfControl);

	FText NewText = FText::FromString(pageDatas.Text);
	ControlsText->SetText(NewText);
}

void UMainMenu::ShowCurrentTutorialPage() {
	ManageTutorialPageSteppingButtons();

	FTutorialPageDatas pageDatas = TutorialConfig->GetTutorialPageDatas(CurrentPageIndex);
	TutorialImage->SetBrushFromTexture(pageDatas.Image);

	FText NewText = FText::FromString(pageDatas.Text);
	TutorialText->SetText(NewText);
}

void UMainMenu::ManageTutorialPageSteppingButtons() {
	TutorialLeftPage->SetIsEnabled(CurrentPageIndex > 0);
	TutorialRightPage->SetIsEnabled(CurrentPageIndex < TutorialConfig->GetTutorialPageCount() - 1);
}

void UMainMenu::ManageControlsPageSteppingButtons() {
	ControlsLeftPage->SetIsEnabled(CurrentPageIndex > 0);
	ControlsRightPage->SetIsEnabled(CurrentPageIndex < ControlsConfig->GetControlsPageCount() - 1);
}

void UMainMenu::BackToMain() {
	SetMainMenuState(EMainMenuState::Main);

	UIPressHappened.Broadcast();
}

void UMainMenu::NewGameOnClick() {

	UIPressHappened.Broadcast();

	ULevelManager* MySubsystem = GetGameInstance()->GetSubsystem<ULevelManager>();
	MySubsystem->LoadLevel(ELevelIdentifier::MainScene, GetWorld());
}

void UMainMenu::HintOnClick() {
	SetMainMenuState(EMainMenuState::Hint);
	CurrentPageIndex = 0;
	ShowCurrentTutorialPage();

	UIPressHappened.Broadcast();
}

void UMainMenu::ControlsOnClick() {
	SetMainMenuState(EMainMenuState::Controls);
	CurrentPageIndex = 0;
	ShowCurrentControlsPage();

	UIPressHappened.Broadcast();
}

void UMainMenu::QuitOnClick() {

	UIPressHappened.Broadcast();

	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}

void UMainMenu::FromTutorialToMainMenuOnClick() {

	UIPressHappened.Broadcast();

	BackToMain();
}

void UMainMenu::TutorialLeftPageOnClick() {

	UIPressHappened.Broadcast();

	if (CurrentPageIndex - 1 >= 0)
	{
		CurrentPageIndex -= 1;
		ShowCurrentTutorialPage();
	}
}

void UMainMenu::TutorialRightPageOnClick() {

	UIPressHappened.Broadcast();

	if (CurrentPageIndex + 1 < TutorialConfig->GetTutorialPageCount())
	{
		CurrentPageIndex += 1;
		ShowCurrentTutorialPage();
	}
}

void UMainMenu::FromControlsToMainMenuOnClick() {
	UIPressHappened.Broadcast();

	BackToMain();
}

void UMainMenu::ControlsLeftPageOnClick() {

	UIPressHappened.Broadcast();

	if (CurrentPageIndex - 1 >= 0)
	{
		CurrentPageIndex -= 1;
		ShowCurrentControlsPage();
	}
}

void UMainMenu::ControlsRightPageOnClick() {

	UIPressHappened.Broadcast();

	if (CurrentPageIndex + 1 < ControlsConfig->GetControlsPageCount())
	{
		CurrentPageIndex += 1;
		ShowCurrentControlsPage();
	}
}

void UMainMenu::ShowState() {
	MainMenuParent->SetVisibility(MainMenuState == EMainMenuState::Main ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	TutorialParent->SetVisibility(MainMenuState == EMainMenuState::Hint ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	ControlsParent->SetVisibility(MainMenuState == EMainMenuState::Controls ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}