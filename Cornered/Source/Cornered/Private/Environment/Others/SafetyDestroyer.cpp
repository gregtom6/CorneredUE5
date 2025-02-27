// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Environment/Others/SafetyDestroyer.h"

ASafetyDestroyer::ASafetyDestroyer() {

    PrimaryActorTick.bCanEverTick = false;
}

void ASafetyDestroyer::BeginPlay()
{
    Super::BeginPlay();

    OnActorBeginOverlap.AddUniqueDynamic(this, &ASafetyDestroyer::OnOverlapBegin);
}

void ASafetyDestroyer::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this && !OtherActor->IsA(ASafetyDestroyer::StaticClass()))
    {
        OtherActor->Destroy();
    }
}