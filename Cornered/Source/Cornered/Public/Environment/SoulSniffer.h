// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulSniffer.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class CORNERED_API ASoulSniffer : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Target;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DissipateTarget;

	
public:	
	// Sets default values for this actor's properties
	ASoulSniffer();

	FVector GetTargetLocation();

	FVector GetDissipateTargetLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
