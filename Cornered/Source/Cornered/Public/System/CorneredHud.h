// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CorneredHud.generated.h"

class UUserWidget;
class UAudioComponent;
class ACorneredCharacter;

UCLASS()
class CORNERED_API ACorneredHud : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TArray<TSubclassOf<UUserWidget>> WidgetClasses;

private:

	UPROPERTY()
	TArray<TObjectPtr<UUserWidget>> WidgetInstances;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> BGMComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> AmbientComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> StaticNoiseComp;

private:

	UFUNCTION()
	void OnCharacterDefeated(ACorneredCharacter* DefeatedCharacter);

	UFUNCTION()
	void OnSoulEjected();

	UFUNCTION()
	void OnSoulDissipated();

public:
	ACorneredHud();
	virtual void BeginPlay() override;

protected:

	UFUNCTION()
	void OnTimerOverHappened();
};
