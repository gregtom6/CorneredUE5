// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Menus/GameWinMenu.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include "System/LevelManager.h"
#include "Configs/DeveloperSettings/ConfigLevelsDevSettings.h"

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

	ULevelManager* MySubsystem = GetGameInstance()->GetSubsystem<ULevelManager>();
	MySubsystem->LoadLevel(ELevelIdentifier::MainScene, GetWorld());
}

void UGameWinMenu::QuitOnClick() {

	UIPressHappened.Broadcast();

	ULevelManager* MySubsystem = GetGameInstance()->GetSubsystem<ULevelManager>();
	MySubsystem->LoadLevel(ELevelIdentifier::MainMenu, GetWorld());
}