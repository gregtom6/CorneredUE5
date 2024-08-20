// @ 15.07.2024 Tamas Gregus. All Rights Reserved.


#include "CorneredObjectPool.h"
#include "CorneredPooledObject.h"

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
		toReturnActor->AttachToActor(nullptr, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		toReturnActor->SetActorHiddenInGame(false);
		toReturnActor->SetActorEnableCollision(true);
		toReturnActor->SetActorTickEnabled(true);
		toReturn->_IsActive = true;
		return toReturnActor;
	}

	if (!_PooledObjectData[currentPool]._CanGrow) { return nullptr; }


	FActorSpawnParameters spawnParams;
	spawnParams.Name = FName(FString::Printf(TEXT("%s"), *_PooledObjectData[currentPool]._ActorName));
	spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* spawnedActor = GetWorld()->SpawnActor(_PooledObjectData[currentPool]._ActorTemplate,
		&FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams);
	UCorneredPooledObject* poolComp = NewObject<UCorneredPooledObject>(spawnedActor);
	poolComp->RegisterComponent();
	spawnedActor->AddInstanceComponent(poolComp);
	poolComp->Init(this);
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
	returningActor->SetActorHiddenInGame(true);
	returningActor->SetActorEnableCollision(false);
	returningActor->SetActorTickEnabled(false);
	returningActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
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
		spawnParams.Name = FName(FString::Printf(TEXT("%s"), *_PooledObjectData[poolIndex]._ActorName));
		spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		for (int objectIndex = 0; objectIndex < _PooledObjectData[poolIndex]._PoolSize; objectIndex++)
		{

			AActor* spawnedActor = GetWorld()->SpawnActor(_PooledObjectData[poolIndex]._ActorTemplate,
				&FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams);
			UCorneredPooledObject* poolComp = NewObject<UCorneredPooledObject>(spawnedActor);
			poolComp->RegisterComponent();
			spawnedActor->AddInstanceComponent(poolComp);
			poolComp->Init(this);
			currentPool._PooledObjects.Add(poolComp);
			spawnedActor->SetActorHiddenInGame(true);
			spawnedActor->SetActorEnableCollision(false);
			spawnedActor->SetActorTickEnabled(false);
			spawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		_Pools.Add(currentPool);
	}

	bAlreadyInitialized = true;
	InitializationHappened.Broadcast();
}

void ACorneredObjectPool::RegenItem(int poolIndex, int positionIndex)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Name = FName(FString::Printf(TEXT("%s"), *_PooledObjectData[poolIndex]._ActorName));
	spawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* spawnedActor = GetWorld()->SpawnActor(_PooledObjectData[poolIndex]._ActorTemplate,
		&FVector::ZeroVector, &FRotator::ZeroRotator, spawnParams);
	UCorneredPooledObject* poolComp = NewObject<UCorneredPooledObject>(spawnedActor);
	poolComp->RegisterComponent();
	spawnedActor->AddInstanceComponent(poolComp);
	poolComp->Init(this);
	_Pools[poolIndex]._PooledObjects.Insert(poolComp, positionIndex);
	spawnedActor->SetActorHiddenInGame(true);
	spawnedActor->SetActorEnableCollision(false);
	spawnedActor->SetActorTickEnabled(false);
	spawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
