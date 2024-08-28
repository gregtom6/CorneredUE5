// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CorneredButton.h"
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

public:
	ATimeZeroerButton();

	void Interact() override;

};
