// @ 15.07.2024 Tamas Gregus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorneredObjectPool.generated.h"

class UCorneredPooledObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPoolerCleanupSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitializationHappened);

USTRUCT(BlueprintType)
struct FSingleObjectPool
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<UCorneredPooledObject>> _PooledObjects;
};

USTRUCT(BlueprintType)
struct FPooledObjectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> _ActorTemplate;
	UPROPERTY(EditAnywhere)
	int32 _PoolSize;
	UPROPERTY(EditAnywhere)
	bool _CanGrow;
	UPROPERTY(EditAnywhere)
	FString _ActorName;

	FPooledObjectData()
	{
		_ActorTemplate = nullptr;
		_PoolSize = 1;
		_CanGrow = false;
		_ActorName = "default";
	}
};


UCLASS()
class CORNERED_API ACorneredObjectPool : public AActor
{
	GENERATED_BODY()

public:
	FPoolerCleanupSignature OnPoolerCleanup;
	FInitializationHappened InitializationHappened;

	bool bAlreadyInitialized;

private:
	UPROPERTY(EditAnywhere)
	TArray<FPooledObjectData> _PooledObjectData;

	UPROPERTY(VisibleInstanceOnly)
	TArray<FSingleObjectPool> _Pools;

public:
	ACorneredObjectPool();


	UFUNCTION()
	void Broadcast_PoolerCleanup();

	UFUNCTION()
	AActor* GetPooledActor(FString name);

	UFUNCTION()
	void RecyclePooledObject(UCorneredPooledObject* poolCompRef);

	UFUNCTION()
	void RecycleActor(AActor* pooledActor);

protected:
	virtual void BeginPlay() override;

private:

	UCorneredPooledObject* SpawnAndSetupPooledObject(FActorSpawnParameters spawnParams, AActor*& SpawnedActor, int32 poolIndex);

	void SetupActorSpawnParameters(FActorSpawnParameters& spawnParams, int32 poolIndex);

	void SetActorVisibility(AActor* Actor, bool ShouldActivate, AActor* Parent);

	void RegenItem(int32 poolIndex, int32 positionIndex);
};
