// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CorneredPooledObject.generated.h"

class ACorneredObjectPool;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CORNERED_API UCorneredPooledObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCorneredPooledObject();

public:	

	UPROPERTY(VisibleInstanceOnly)
		bool _IsActive;

	void Init(ACorneredObjectPool* owner);

	UFUNCTION()
		void RecycleSelf();

private:

	TObjectPtr<ACorneredObjectPool> _ObjectPool;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
