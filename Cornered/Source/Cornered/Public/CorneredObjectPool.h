// Fill out your copyright notice in the Description page of Project Settings.

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
		int _PoolSize;
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
	// Sets default values for this actor's properties
	ACorneredObjectPool();

	UPROPERTY()
		FPoolerCleanupSignature OnPoolerCleanup;

	UFUNCTION()
		void Broadcast_PoolerCleanup();

	UFUNCTION()
		AActor* GetPooledActor(FString name);

	UFUNCTION()
		void RecyclePooledObject(UCorneredPooledObject* poolCompRef);

	UFUNCTION()
		void RecycleActor(AActor* pooledActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TArray<FPooledObjectData> _PooledObjectData;

	UPROPERTY(VisibleInstanceOnly)
		TArray<FSingleObjectPool> _Pools;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FInitializationHappened InitializationHappened;

	UPROPERTY()
		bool bAlreadyInitialized;

private:

	void RegenItem(int poolIndex, int positionIndex);
};
