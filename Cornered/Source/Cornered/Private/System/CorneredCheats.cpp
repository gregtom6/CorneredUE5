// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredCheats.h"
#include <Kismet/GameplayStatics.h>
#include "Characters/Systems/EnemyCharacter.h"
#include "Characters/ActorComponents/HideSpotFinder.h"
#include "Characters/ActorComponents/EnemyWeapon.h"

UCorneredCheats::UCorneredCheats() {
	bEnabled = false;

	RegisterCommands();
}

void UCorneredCheats::RegisterCommands() {

	if (IConsoleManager::Get().IsNameRegistered(TEXT("ToggleAIDebugDrawings"))) {
		IConsoleManager::Get().UnregisterConsoleObject(TEXT("ToggleAIDebugDrawings"));
	}

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("ToggleAIDebugDrawings"),
		TEXT("Toggles the Cornered AI debug drawings"),
		FConsoleCommandDelegate::CreateUObject(this, &UCorneredCheats::ManageAIDebugDrawings),
		ECVF_Cheat
	);
}

void UCorneredCheats::ManageAIDebugDrawings() {
	bEnabled = !bEnabled;

	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundActors);

	ManageAIHideSpotDrawings(FoundActors);

	ManageEnemyWeaponDebugDrawings(FoundActors);
}

void UCorneredCheats::ManageAIHideSpotDrawings(TArray<AActor*> FoundActors) {

	for (int i = 0; i < FoundActors.Num(); i++) {

		UActorComponent* FoundComponent = FoundActors[i]->GetComponentByClass(UHideSpotFinder::StaticClass());

		if (FoundComponent->IsA(UHideSpotFinder::StaticClass())) {
			UHideSpotFinder* hideSpotFinder = Cast<UHideSpotFinder>(FoundComponent);

			hideSpotFinder->ManageDebugDrawings(bEnabled);
		}
	}

}

void UCorneredCheats::ManageEnemyWeaponDebugDrawings(TArray<AActor*> FoundActors) {

	for (int i = 0; i < FoundActors.Num(); i++) {

		UActorComponent* FoundComponent = FoundActors[i]->GetComponentByClass(UEnemyWeapon::StaticClass());

		if (FoundComponent->IsA(UEnemyWeapon::StaticClass())) {
			UEnemyWeapon* enemyWeapon = Cast<UEnemyWeapon>(FoundComponent);

			enemyWeapon->ManageDebugDrawings(bEnabled);
		}
	}
}