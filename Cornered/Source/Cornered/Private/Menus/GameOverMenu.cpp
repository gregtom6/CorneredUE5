// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "GameOverMenu.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

void UGameOverMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (Restart)
	{
		Restart->OnClicked.AddDynamic(this, &UGameOverMenu::RestartOnClick);
	}

	if (Quit)
	{
		Quit->OnClicked.AddDynamic(this, &UGameOverMenu::QuitOnClick);
	}
}

void UGameOverMenu::RestartOnClick() {

	UIPressHappened.Broadcast();

	FString levelName = GameLevel.GetAssetName();
	FName LevelName = FName(*levelName);
	UGameplayStatics::OpenLevel(this, LevelName);
}

void UGameOverMenu::QuitOnClick() {

	UIPressHappened.Broadcast();

	FString levelName = MainMenuLevel.GetAssetName();
	FName LevelName = FName(*levelName);
	UGameplayStatics::OpenLevel(this, LevelName);
}