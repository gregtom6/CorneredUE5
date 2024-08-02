// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "EnemyCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <PlayerCharacterAnimInstance.h>
#include "EnemyWeapon.h"
#include "Camera/CameraComponent.h"
#include "EquipmentVisualizer.h"
#include "Components/SceneComponent.h"
#include "Inventory.h"
#include "PaperSpriteComponent.h"
#include "CooldownIndicator.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyHealth.h"
#include "EnemyController.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyWeaponComp = CreateDefaultSubobject<UEnemyWeapon>(TEXT("EnemyWeaponComp"));

	CooldownIndicatorParentComp = CreateDefaultSubobject<USceneComponent>(TEXT("CooldownIndicatorParentComp"));

	PaperSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComp"));

	CooldownIndicatorComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CooldownIndicatorComp"));

	EquipmentVisualizer = CreateDefaultSubobject<UEquipmentVisualizer>(TEXT("EquipmentVisualizer"));

	InventoryComp = CreateDefaultSubobject<UInventory>(TEXT("InventoryComp"));

	EnemyHealthComp = CreateDefaultSubobject<UEnemyHealth>(TEXT("EnemyHealthComp"));

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	CooldownIndicatorManagementComp = CreateDefaultSubobject<UCooldownIndicator>(TEXT("CooldownIndicatorManagementComp"));

	CameraComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CooldownIndicatorParentComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RightArmSocket"));
	PaperSpriteComp->AttachToComponent(CooldownIndicatorParentComp, FAttachmentTransformRules::KeepRelativeTransform);
	CooldownIndicatorComp->AttachToComponent(PaperSpriteComp, FAttachmentTransformRules::KeepRelativeTransform);

	CooldownIndicatorParentComp->SetRelativeLocation(FVector(93.663588f, -25.109281f, -89.030848f));
	CooldownIndicatorParentComp->SetRelativeRotation(FRotator(-31.553031f, -16.355435f, -45.163447f));
	CooldownIndicatorParentComp->SetRelativeScale3D(FVector(20.0f, 20.0f, 49.375f));

	PaperSpriteComp->SetRelativeScale3D(FVector(1.0f, 1.684211f, 1.684211f));

	CooldownIndicatorComp->SetRelativeLocation(FVector(0.f, -0.1725f, 0.f));

	CooldownIndicatorManagementComp->SetComponents(CooldownIndicatorComp, EnemyWeaponComp);

	/*
	UWorld* World = GetWorld();
	AGameModeBase* GameMode = World->GetAuthGameMode();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	APawn* PlayerPawn = PlayerController->GetPawn();

	EnemyController = Cast<AEnemyController>(GetController());
	EnemyController->MoveToActor(PlayerPawn);
	*/
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ACorneredPlayerController* CorneredPlayerController = Cast<ACorneredPlayerController>(PlayerController);
	UPlayerCharacterAnimInstance* animInst = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (animInst) {
		if (CorneredPlayerController && animInst->LegState != (int)CorneredPlayerController->GetMovementState()) {
			animInst->LegState = (int)CorneredPlayerController->GetMovementState();
		}

		if (EnemyWeaponComp && animInst->UseWeapon != EnemyWeaponComp->IsThereEquippedWeapon()) {
			animInst->UseWeapon = EnemyWeaponComp->IsThereEquippedWeapon();
		}
	}
	*/
	/*
	FVector Velocity = GetCharacterMovement()->Velocity;
	if (!Velocity.IsZero())
	{
		FRotator TargetRotation = Velocity.Rotation();

		// Optionally interpolate to smooth the rotation
		//FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 5.0f); // 5.0f is the interpolation speed

		SetActorRotation(TargetRotation);
	}
	*/
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::Chase(APawn* TargetPawn) {

}