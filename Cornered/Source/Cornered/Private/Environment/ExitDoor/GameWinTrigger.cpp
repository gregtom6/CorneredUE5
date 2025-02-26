// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/ExitDoor/GameWinTrigger.h"
#include "System/LevelManager.h"
#include "Configs/DeveloperSettings/ConfigLevelsDevSettings.h"
#include "System/CorneredGameInstance.h"
#include "System/ProgressionGameState.h"

void AGameWinTrigger::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddUniqueDynamic(this, &AGameWinTrigger::OnOverlapBegin);
}

void AGameWinTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    // Check if OtherActor is valid
    if (OtherActor && OtherActor != this)
    {
        UCorneredGameInstance* MyGameInstance = Cast<UCorneredGameInstance>(GetWorld()->GetGameInstance());
        AProgressionGameState* MyGameState = Cast<AProgressionGameState>(GetWorld()->GetGameState());
        if (MyGameState && MyGameInstance)
        {
            MyGameInstance->SaveEndLevelStats(MyGameState);
        }

        ULevelManager* MySubsystem = GetGameInstance()->GetSubsystem<ULevelManager>();
        MySubsystem->LoadLevel(ELevelIdentifier::GameWinScene, GetWorld());
    }
}