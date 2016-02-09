// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "PlayerCarCode.h"
#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

APlayerCarCode* Util::GetLocalPlayer(UWorld* world)
{
	return Cast<APlayerCarCode>(world->GetFirstPlayerController()->GetPawn());
}

APlayerCarCode* Util::GetPlayerCar(APlayerController* player)
{
	return Cast<APlayerCarCode>(player->GetPawn());
}

int32 Util::GetNumPlayers(UWorld* world)
{
	int32 numPlayers = 0;

	for (FConstPlayerControllerIterator iter = world->GetPlayerControllerIterator(); iter; ++iter)
		numPlayers++;

	return numPlayers;
}

//TODO: Check if this function is even needed
//TODO: If needed fix this
float Util::GetDistanceToPlayer(const AActor* object, const APlayerCarCode* player)
{
	FVector objectLoc = object->GetActorLocation();
	FVector playerLoc = player->GetActorLocation();
	FVector diff = objectLoc - playerLoc;

	/*UCapsuleComponent* capsule = nullptr;
	UBoxComponent* box = player->getHitBox();*/
	//if (capsule == NULL)
		return diff.Size();

	//float diagonal;
	//FBoxSphereBounds bounds = box->Bounds;
	//float radius = bounds.SphereRadius;

	//float objectRadius = 0.0f;
	//

	//return 0.0f;
}