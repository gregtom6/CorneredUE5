// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;
class UConfig_Time;
class UConfig_Visual;
class ACorneredCharacter;

UCLASS()
class CORNERED_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> Health;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> DeltaHealth;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Time> TimeConfig;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConfig_Visual> VisualConfig;

private:

	float PreviousHealthPercent;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	UFUNCTION()
	void OnCharacterShotReceived(ACorneredCharacter* Character);
};
