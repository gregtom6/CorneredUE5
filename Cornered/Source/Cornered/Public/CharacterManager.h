// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterManager.generated.h"

class UConfig_Character_General;
class AEnemyCharacter;
class ACorneredGameMode;

UCLASS()
class CORNERED_API ACharacterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
		TArray<AActor*> EnemyPossibleStartingPositions;

	UPROPERTY(EditAnywhere)
		UConfig_Character_General* CharacterConfig;

	UFUNCTION()
		FVector GetRandomPosition();
};
