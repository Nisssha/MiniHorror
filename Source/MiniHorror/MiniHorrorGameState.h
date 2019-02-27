// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MiniHorrorGameState.generated.h"

/**
 * 
 */
UCLASS()
class MINIHORROR_API AMiniHorrorGameState : public AGameStateBase
{
	GENERATED_BODY()

	int ObjectsCollectedNum = 0;
	
public:

	DECLARE_EVENT_OneParam(AMiniHorrorGameState, FObjectCollected, int32)
	FObjectCollected OnObjectCollected;

	void ObjectCollected();

};
