// Fill out your copyright notice in the Description page of Project Settings.


#include "SafetyDestroyer.h"

ASafetyDestroyer::ASafetyDestroyer()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // Set up the overlap event
    OnActorBeginOverlap.AddUniqueDynamic(this, &ASafetyDestroyer::OnOverlapBegin);
}

void ASafetyDestroyer::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && OtherActor != this && !OtherActor->IsA(ASafetyDestroyer::StaticClass()))
    {
        OtherActor->Destroy();
    }
}