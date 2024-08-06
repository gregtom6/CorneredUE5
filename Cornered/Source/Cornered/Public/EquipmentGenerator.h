// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentGenerator.generated.h"

class UCharacterSpawner;
class UConfig_Equipment;
class AEnemyCharacter;

UCLASS()
class CORNERED_API AEquipmentGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipmentGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

	UFUNCTION()
		void GenerateEquipment(AEnemyCharacter* EnemyCharacter);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
		UConfig_Equipment* EquipmentConfig;
};
