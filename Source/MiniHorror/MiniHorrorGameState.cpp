// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniHorrorGameState.h"


void AMiniHorrorGameState::ObjectCollected()
{
	ObjectsCollectedNum++;
	this->OnObjectCollected.Broadcast(ObjectsCollectedNum);
}

