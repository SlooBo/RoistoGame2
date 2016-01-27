// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "PlayerCar.h"
#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

APlayerCar* Util::GetLocalPlayer(UWorld* world)
{
	return Cast<APlayerCar>(world->GetFirstPlayerController()->GetPawn());
}