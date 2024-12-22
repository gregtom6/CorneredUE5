// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageVisualizer.generated.h"

class UConfig_DamageVisual;
class AEnemyCharacter;
class UCharacterHealth;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UDamageVisualizer : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TObjectPtr<AEnemyCharacter> Enemy;

	UPROPERTY()
	TObjectPtr<UCharacterHealth> CharacterHealth;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_DamageVisual> DamageVisualConfig;

public:	
	// Sets default values for this component's properties
	UDamageVisualizer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEnemyGenerated(AEnemyCharacter* EnemyCharacter);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ProcessDamage();
};
