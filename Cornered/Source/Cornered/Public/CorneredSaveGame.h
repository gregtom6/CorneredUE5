// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CorneredSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CORNERED_API UCorneredSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere)
        int32 CurrentUnlockLevel;

};
