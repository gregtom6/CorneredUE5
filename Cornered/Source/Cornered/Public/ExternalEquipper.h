// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Config_Equipment.h"
#include "ExternalEquipper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UExternalEquipper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExternalEquipper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void Equip(FItemDatas weapon, FItemDatas shield, FItemDatas additional);
		
};
