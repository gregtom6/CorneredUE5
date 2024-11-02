// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "System/CorneredObjectPool.h"
#include "System/CorneredPooledObject.h"

ACorneredObjectPool::ACorneredObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACorneredObjectPool::Broadcast_PoolerCleanup()
{
	OnPoolerCleanup.Broadcast();
}

AActor* ACorneredObjectPool::GetPooledActor(FString name)
{
	int poolCount = _Pools.Num();
	int currentPool = -1;
	for (int i = 0; i < poolCount; i++)
	{
		if (_PooledObjectData[i]._ActorName == name)
		{
			currentPool = i;
			break;
		}
	}

	if (currentPool == -1) { return nullptr; }

	int pooledObjectCount = _Pools[currentPool]._PooledObjects.Num();
	int firstAvailable = -1;
	for (int i = 0; i < pooledObjectCount; i++)
	{
		if (_Pools[currentPool]._PooledObjects[i] != nullptr)
		{
			if (!_Pools[currentPool]._PooledObjects[i]->_IsActive)
			{
				firstAvailable = i;
				break;
			}
		}
		else
		{
			RegenItem(currentPool, i);
			firstAvailable = i;
			break;
		}
	}

	if (firstAvailable >= 0)
	{
		UCorneredPooledObject* toReturn = _Pools[currentPool]._PooledObjects[firstAvailable];
		OnPoolerCleanup.AddUniqueDynamic(toReturn, &UCorneredPooledObject::RecycleSelf);
		AActor* toReturnActor = toReturn->GetOwner();

		SetActorVisibility(toReturnActor, true, nullptr);
		toReturn->_IsActive = true;
		return toReturnActor;
	}

	if (!_PooledObjectData[currentPool]._CanGrow) { return nullptr; }


	FActorSpawnParameters spawnParams;
	AActor* spawnedActor = nullptr;
	SetupActorSpawnParameters(spawnParams, currentPool);
	UCorneredPooledObject* poolComp = SpawnAndSetupPooledObject(spawnParams, spawnedActor, currentPool);

	_Pools[currentPool]._PooledObjects.Add(poolComp);
	spawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	OnPoolerCleanup.AddUniqueDynamic(poolComp, &UCorneredPooledObject::RecycleSelf);
	poolComp->_IsActive = true;
	return spawnedActor;
}

void ACorneredObjectPool::RecyclePooledObject(UCorneredPooledObject* poolCompRef)
{
	OnPoolerCleanup.RemoveDynamic(poolCompRef, &UCorneredPooledObject::RecycleSelf);
	poolCompRef->_IsActive = false;
	AActor* returningActor = poolCompRef->GetOwner();

	SetActorVisibility(returningActor, false, this);
}

void ACorneredObjectPool::RecycleActor(AActor* pooledActor)
{
	if (UCorneredPooledObject* poolCompRef = pooledActor->FindComponentByClass<UCorneredPooledObject>())
	{
		RecyclePooledObject(poolCompRef);
	}
}

// Called when the game starts or when spawned
void ACorneredObjectPool::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters spawnParams;
	for (int poolIndex = 0; poolIndex < _PooledObjectData.Num(); poolIndex++)
	{
		FSingleObjectPool currentPool;
		SetupActorSpawnParameters(spawnParams, poolIndex);
		
		for (int objectIndex = 0; objectIndex < _PooledObjectData[poolIndex]._PoolSize; objectIndex++)
		{
			AActor* spawnedActor = nullptr;
			UCorneredPooledObject* poolComp = SpawnAndSetupPooledObject(spawnParams,spawnedActor, poolIndex);
			SetActorVisibility(spawnedActor, false, this);

			currentPool._PooledObjects.Add(poolComp);
		}
		_Pools.Add(currentPool);
	}

	bAlreadyInitialized = true;
	InitializationHappened.Broadcast();
}

void ACorneredObjectPool::SetupActorSpawnParameters(FActorSpawnParameters& spawnParams, int poolIndex) {
	spawnParams.Name = FName(FString::Printf(TEXT("%s"), *_PooledObjectData[poolIndex]._ActorName));
	spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void ACorneredObjectPool::RegenItem(int poolIndex, int positionIndex)
{
	FActorSpawnParameters spawnParams;
	SetupActorSpawnParameters(spawnParams, poolIndex);
	AActor* spawnedActor = nullptr;
	UCorneredPooledObject* poolComp=SpawnAndSetupPooledObject(spawnParams, spawnedActor, poolIndex);
	SetActorVisibility(spawnedActor, false, this);
	_Pools[poolIndex]._PooledObjects.Insert(poolComp, positionIndex);
}

UCorneredPooledObject* ACorneredObjectPool::SpawnAndSetupPooledObject(FActorSpawnParameters spawnParams, AActor*& spawnedActor,int poolIndex) {
	
	if (!GetWorld() || GetWorld()->bIsTearingDown)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is invalid or tearing down. Aborting SpawnActor."));
		return nullptr;  // or handle appropriately
	}
	
	spawnedActor = GetWorld()->SpawnActor(_PooledObjectData[poolIndex]._ActorTemplate,
		&FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams);
	UCorneredPooledObject* poolComp = NewObject<UCorneredPooledObject>(spawnedActor);
	poolComp->RegisterComponent();
	spawnedActor->AddInstanceComponent(poolComp);
	poolComp->Init(this);

	return poolComp;
}

void ACorneredObjectPool::SetActorVisibility(AActor* Actor, bool ShouldActivate, AActor* parent) {
	Actor->SetActorHiddenInGame(!ShouldActivate);
	Actor->SetActorEnableCollision(ShouldActivate);
	Actor->SetActorTickEnabled(ShouldActivate);
	Actor->AttachToActor(parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}