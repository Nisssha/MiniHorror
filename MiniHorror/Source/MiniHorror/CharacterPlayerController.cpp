// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterPlayerController.h"
#include "PlayerCharacter.h"
#include "CollectableComponent.h"
#include "Engine.h"
#include "MiniHorrorGameState.h"

ACharacterPlayerController::ACharacterPlayerController()
{
}

void ACharacterPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	playerCharacter = Cast<APlayerCharacter>(InPawn);
}

void ACharacterPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacterPlayerController::StopJumping);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterPlayerController::TryCollect);

	InputComponent->BindAxis("MoveForward", this, &ACharacterPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACharacterPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACharacterPlayerController::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ACharacterPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &ACharacterPlayerController::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ACharacterPlayerController::LookUpAtRate);
}

void ACharacterPlayerController::Jump()
{
	if (playerCharacter != nullptr)
	{
		playerCharacter->Jump();
	}
}

void ACharacterPlayerController::StopJumping()
{
	if (playerCharacter != nullptr)
	{
		playerCharacter->StopJumping();
	}
}

void ACharacterPlayerController::MoveForward(float val)
{
	if (playerCharacter != nullptr && val != 0.f)
	{
		playerCharacter->MoveForward(val);
	}
}

void ACharacterPlayerController::MoveRight(float val)
{
	if (playerCharacter != nullptr && val != 0.f)
	{
		playerCharacter->MoveRight(val);
	}
}

void ACharacterPlayerController::AddControllerYawInput(float val)
{
	if (playerCharacter != nullptr && val != 0.f)
	{
		playerCharacter->AddControllerYawInput(val);
	}
}

void ACharacterPlayerController::AddControllerPitchInput(float val)
{
	if (playerCharacter != nullptr && val != 0.f)
	{
		playerCharacter->AddControllerPitchInput(val);
	}
}

void ACharacterPlayerController::TurnAtRate(float val)
{
	if (playerCharacter != nullptr && val != 0.f)
	{
		playerCharacter->TurnAtRate(val);
	}
}

void ACharacterPlayerController::LookUpAtRate(float val)
{
	if (playerCharacter != nullptr && val != 0.f)
	{
		playerCharacter->LookUpAtRate(val);
	}
}

void ACharacterPlayerController::Collect(class UCollectableComponent* collectable)
{
	if (collectable != nullptr)
	{
		OwnedCollectables++;
		collectable->GetOwner()->Destroy();
		GetWorld()->GetGameState<AMiniHorrorGameState>()->ObjectCollected();
	}
}

void ACharacterPlayerController::TryCollect()
{
	UCameraComponent* CameraComponent = nullptr;

	for (UActorComponent* Component : playerCharacter->GetComponents())
	{
		if (Cast<UCameraComponent>(Component) != nullptr)
		{
			CameraComponent = Cast<UCameraComponent>(Component);
			break;
		}
	}

	FHitResult hitObject;
	FVector Start = CameraComponent->GetComponentLocation();

	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector End = ((ForwardVector * 1000.f) + Start);

	GetWorld()->LineTraceSingleByChannel(hitObject, Start, End, ECollisionChannel::ECC_Visibility);

	if (hitObject.Actor != nullptr)
	{
		for (UActorComponent* comp : hitObject.Actor.Get()->GetComponents())
		{
			if (Cast<UCollectableComponent>(comp) != nullptr)
			{
				Collect(Cast<UCollectableComponent>(comp));
			}
		}
	}
}

