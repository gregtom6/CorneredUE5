// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Environment/Interactables/CorneredButton.h"
#include "Configs/DataAssets/Config_Others.h"
#include "TimeZeroerButton.generated.h"

class UStaticMeshComponent;

UCLASS()
class CORNERED_API ATimeZeroerButton : public ACorneredButton
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> TimeButtonStaticMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Others> OthersConfig;

	ETimerButtonState SelfState;

public:
	ATimeZeroerButton();

	void Interact() override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTimerOverHappened();

	UFUNCTION()
	void OnNewMatchStarted();

private:

	void ManageButton(ETimerButtonState State);

};
