// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CorneredPooledObject.h"
#include "CorneredObjectPool.h"

// Sets default values for this component's properties
UCorneredPooledObject::UCorneredPooledObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UCorneredPooledObject::Init(ACorneredObjectPool* owner)
{
	_IsActive = false;
	_ObjectPool = owner;

}

void UCorneredPooledObject::RecycleSelf()
{
	_ObjectPool->RecyclePooledObject(this);
}

// Called when the game starts
void UCorneredPooledObject::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCorneredPooledObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCorneredPooledObject::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	_ObjectPool->OnPoolerCleanup.RemoveDynamic(this, &UCorneredPooledObject::RecycleSelf);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}