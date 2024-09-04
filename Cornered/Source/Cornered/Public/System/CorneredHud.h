// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CorneredHud.generated.h"

class UUserWidget;
class UAudioComponent;
class ACharacter;

UCLASS()
class CORNERED_API ACorneredHud : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TArray<TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> WidgetInstances;

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> BGMComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> AmbientComp;

private:

	UFUNCTION()
	void OnCharacterDefeated(ACharacter* DefeatedCharacter);

public:
	ACorneredHud();
	virtual void BeginPlay() override;

protected:

	UFUNCTION()
	void OnTimerOverHappened();
};
