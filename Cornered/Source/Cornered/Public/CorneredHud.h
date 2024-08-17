// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CorneredHud.generated.h"

class UUserWidget;
class UAudioComponent;
class ACharacter;
/**
 * 
 */
UCLASS()
class CORNERED_API ACorneredHud : public AHUD
{
	GENERATED_BODY()

		ACorneredHud();

private:

	UPROPERTY(EditAnywhere)
		UAudioComponent* BGMComp;

	UPROPERTY(EditAnywhere)
		UAudioComponent* AmbientComp;

	UFUNCTION()
		void OnCharacterDefeated(ACharacter* DefeatedCharacter);
	
public:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TArray<TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
		TArray<UUserWidget*> WidgetInstances;

	UFUNCTION()
		void OnTimerOverHappened();
};
