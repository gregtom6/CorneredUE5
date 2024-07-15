// Fill out your copyright notice in the Description page of Project Settings.


#include "CorneredButton.h"
#include "Components/AudioComponent.h"


// Sets default values
ACorneredButton::ACorneredButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PressAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PressAudio"));
}

// Called when the game starts or when spawned
void ACorneredButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACorneredButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACorneredButton::Interact() {

	PressAudio->Play();

	PressHappened.Broadcast();
}