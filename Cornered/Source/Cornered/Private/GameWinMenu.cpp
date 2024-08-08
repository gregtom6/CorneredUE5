// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "GameWinMenu.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

void UGameWinMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (Restart)
	{
		Restart->OnClicked.AddDynamic(this, &UGameWinMenu::RestartOnClick);
	}

	if (Quit)
	{
		Quit->OnClicked.AddDynamic(this, &UGameWinMenu::QuitOnClick);
	}
}

void UGameWinMenu::RestartOnClick() {

	UIPressHappened.Broadcast();

	FString levelName = GameLevel.GetAssetName();
	FName LevelName = FName(*levelName);
	UGameplayStatics::OpenLevel(this, LevelName);
}

void UGameWinMenu::QuitOnClick() {

	UIPressHappened.Broadcast();

	FString levelName = MainMenuLevel.GetAssetName();
	FName LevelName = FName(*levelName);
	UGameplayStatics::OpenLevel(this, LevelName);
}