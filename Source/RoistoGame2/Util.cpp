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

APlayerCar* Util::GetPlayerCar(APlayerController* player)
{
	return Cast<APlayerCar>(player->GetPawn());
}

int32 Util::GetNumPlayers(UWorld* world)
{
	int32 numPlayers = 0;

	for (FConstPlayerControllerIterator iter = world->GetPlayerControllerIterator(); iter; ++iter)
		numPlayers++;

	return numPlayers;
}

float Util::GetDistanceToPlayer(const AActor* object, const APlayerCar* player)
{
	FVector objectLoc = object->GetActorLocation();
	FVector playerLoc = player->GetActorLocation();
	FVector diff = objectLoc - playerLoc;

	UCapsuleComponent* capsule = nullptr;
	UBoxComponent* box = player->getHitBox();
	if (capsule == NULL)
		return diff.Size();

	float diagonal;
	FBoxSphereBounds bounds = box->Bounds;
	float radius = bounds.SphereRadius;

	float objectRadius = 0.0f;
	

	return 0.0f;
}