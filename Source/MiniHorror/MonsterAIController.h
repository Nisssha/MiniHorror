// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class MINIHORROR_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

		AMonsterAIController(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION()
		void OnPerceptionUpdated(TArray<AActor*> actors);

	UFUNCTION()
		void OnCollectiblePickedUp(int32 collectibleNum);

		FAISenseID DominantSenseId;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
