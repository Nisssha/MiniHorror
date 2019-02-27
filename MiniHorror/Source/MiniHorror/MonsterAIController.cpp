// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAIController.h"
#include "MiniHorrorGameState.h"
#include "Engine/World.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "GameFramework/CharacterMovementComponent.h"


AMonsterAIController::AMonsterAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetGenericTeamId(FGenericTeamId(1));

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnPerceptionUpdated);
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameState<AMiniHorrorGameState>()->OnObjectCollected.AddUObject(this, &AMonsterAIController::OnCollectiblePickedUp);


	TSubclassOf<UAISense> dominantsense = PerceptionComponent->GetDominantSense();
	DominantSenseId = dominantsense.GetDefaultObject()->GetSenseID();
}

void AMonsterAIController::OnPerceptionUpdated(TArray<AActor*> actors)
{
	MoveToActor(actors[0], -1.0f, true, false);
}

void AMonsterAIController::OnCollectiblePickedUp(int32 collectibleNums)
{
	//Adjust senses and speed
	UAISenseConfig* hearingConfig = PerceptionComponent->GetSenseConfig(DominantSenseId);

	hearingConfig->SetMaxAge(hearingConfig->GetMaxAge() * 2);
	
	for (UActorComponent* comp : GetPawn()->GetComponents())
	{
		if (Cast<UCharacterMovementComponent>(comp) != nullptr)
		{
			(Cast<UCharacterMovementComponent>(comp))->MaxWalkSpeed = (Cast<UCharacterMovementComponent>(comp))->MaxWalkSpeed * 2;
		}
	}
}

// Called every frame
void AMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> actors;
	PerceptionComponent->GetPerceivedHostileActors(actors);
	if (actors.Num() > 0)
	{
		AActor& closest = *actors[0];

		float lastStimuli = PerceptionComponent->GetYoungestStimulusAge(closest);

		int maxage = PerceptionComponent->GetSenseConfig(DominantSenseId)->GetMaxAge();

		if(lastStimuli > maxage)
		{
			StopMovement();
		}
	}
	else
	{
		StopMovement();
	}
}