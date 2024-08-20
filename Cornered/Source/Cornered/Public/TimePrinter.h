// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimePrinter.generated.h"

class UTextRenderComponent;
class ACorneredGameMode;

UCLASS()
class CORNERED_API ATimePrinter : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
		TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UTextRenderComponent> TimeLeftComp;

	UPROPERTY()
		TObjectPtr<ACorneredGameMode> CorneredGameMode;

public:	
	// Sets default values for this actor's properties
	ATimePrinter();

	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
