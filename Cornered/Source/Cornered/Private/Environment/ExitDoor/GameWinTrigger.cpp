// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/ExitDoor/GameWinTrigger.h"
#include "System/LevelManager.h"
#include "Configs/DeveloperSettings/ConfigLevelsDevSettings.h"

AGameWinTrigger::AGameWinTrigger()
{
    // Bind the overlap event to the function
    OnActorBeginOverlap.AddUniqueDynamic(this, &AGameWinTrigger::OnOverlapBegin);
}

void AGameWinTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    // Check if OtherActor is valid
    if (OtherActor && OtherActor != this)
    {
        ULevelManager* MySubsystem = GetGameInstance()->GetSubsystem<ULevelManager>();
        MySubsystem->LoadLevel(ELevelIdentifier::GameWinScene, GetWorld());
    }
}