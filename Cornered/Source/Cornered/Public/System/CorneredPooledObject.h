// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CorneredPooledObject.generated.h"

class ACorneredObjectPool;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivatedDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CORNERED_API UCorneredPooledObject : public UActorComponent
{
	GENERATED_BODY()


public:

	UPROPERTY(VisibleInstanceOnly)
	bool _IsActive;

	FActivatedDelegate Activated;

private:

	TObjectPtr<ACorneredObjectPool> _ObjectPool;

public:
	UCorneredPooledObject();

	void Init(ACorneredObjectPool* owner);

	UFUNCTION()
	void RecycleSelf();
private:

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
};
