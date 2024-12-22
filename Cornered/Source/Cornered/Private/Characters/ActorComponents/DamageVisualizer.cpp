// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "Characters/ActorComponents/DamageVisualizer.h"
#include "Configs/DataAssets/Config_DamageVisual.h"
#include "Characters/Systems/CharacterSpawner.h"
#include "Characters/Systems/EnemyCharacter.h"
#include "Characters/ActorComponents/CharacterHealth.h"
#include "Algo/Sort.h"
#include "Materials/MaterialInterface.h"

// Sets default values for this component's properties
UDamageVisualizer::UDamageVisualizer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageVisualizer::BeginPlay()
{
	Super::BeginPlay();

	UCharacterSpawner* MySubsystem = GetWorld()->GetSubsystem<UCharacterSpawner>();
	if (MySubsystem)
	{
		MySubsystem->OnEnemyGenerated.AddUniqueDynamic(this, &UDamageVisualizer::OnEnemyGenerated);
	}
	
}

void UDamageVisualizer::OnEnemyGenerated(AEnemyCharacter* EnemyCharacter) {
	Enemy = EnemyCharacter;

	CharacterHealth = EnemyCharacter->FindComponentByClass<UCharacterHealth>();
}


// Called every frame
void UDamageVisualizer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ProcessDamage();
}

void UDamageVisualizer::ProcessDamage() {

	if (DamageVisualConfig == nullptr) {
		return;
	}

	TArray<float> Values = DamageVisualConfig->GetDamagePercentages();

	if (Values.Num() != Enemy->GetCountOfCable()) {
		return;
	}

	Algo::Sort(Values, [](const float& A, const float& B) {
		return A > B;
		});

	for (int i = 0; i < Values.Num(); i++) {

		bool isDamaged = CharacterHealth->GetHealthPercentage() <= Values[i];

		UMaterialInterface* SelectedMaterial = DamageVisualConfig->GetSelectedMaterial(isDamaged);

		Enemy->AttachEndpointOfCable(i, SelectedMaterial, !isDamaged);
	}
}