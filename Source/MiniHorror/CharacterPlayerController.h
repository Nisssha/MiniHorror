// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIHORROR_API ACharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

	int32 OwnedCollectables = 0;
	
	UPROPERTY()
	class APlayerCharacter* playerCharacter = nullptr;

	void Jump();
	void StopJumping();
	void MoveForward(float val);
	void MoveRight(float val);
	void TurnAtRate(float val);
	void LookUpAtRate(float val);
	void AddControllerPitchInput(float val);
	void AddControllerYawInput(float val);

	void TryCollect();

	bool bIsInDialogue = false;

public:

	ACharacterPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	virtual void SetPawn(APawn* InPawn) override;

	void Collect(class UCollectableComponent* collectable);

	
};
