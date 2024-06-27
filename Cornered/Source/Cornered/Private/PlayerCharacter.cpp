// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "CorneredPlayerController.h"
#include <PlayerCharacterAnimInstance.h>
#include "PlayerWeapon.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerWeaponComp = CreateDefaultSubobject<UPlayerWeapon>(TEXT("PlayerWeaponComp"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ACorneredPlayerController* CorneredPlayerController = Cast<ACorneredPlayerController>(PlayerController);
	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (animInst) {
		if (CorneredPlayerController) {
			animInst->LegState = (int)CorneredPlayerController->GetMovementState();
		}

		if (PlayerWeaponComp) {
			animInst->UseWeapon = PlayerWeaponComp->IsThereEquippedWeapon();
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

