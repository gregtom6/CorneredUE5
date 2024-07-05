// Fill out your copyright notice in the Description page of Project Settings.


#include "CorneredGameMode.h"
#include <CorneredHud.h>

ACorneredGameMode::ACorneredGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnBPClass(TEXT("/Game/Data/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController>PlayerControllerBPClass(TEXT("/Game/Data/Blueprints/BP_CorneredPlayerController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ACorneredHud>CorneredHudBPClass(TEXT("/Game/Data/Blueprints/UI/BP_CorneredHud"));
	if (CorneredHudBPClass.Class != nullptr)
	{
		HUDClass = CorneredHudBPClass.Class;
	}
}

