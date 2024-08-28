// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredPooledObject.h"
#include "System/CorneredObjectPool.h"

UCorneredPooledObject::UCorneredPooledObject()
{
	PrimaryComponentTick.bCanEverTick = false;
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

void UCorneredPooledObject::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	_ObjectPool->OnPoolerCleanup.RemoveDynamic(this, &UCorneredPooledObject::RecycleSelf);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}