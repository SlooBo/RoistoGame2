// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "UnrealNetwork.h"
#include "MyGameState.h"
#include "MyPlayerState.h"


AMyGameState::AMyGameState(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
	team1points = 0;
	team2points = 0;
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameState, inGameState);
	DOREPLIFETIME(AMyGameState, teamRaceState);
	DOREPLIFETIME(AMyGameState, stateTimeElapsed);
	DOREPLIFETIME(AMyGameState, stateTimeLength);
	DOREPLIFETIME(AMyGameState, gameTimeElapsed);
	DOREPLIFETIME(AMyGameState, gameTimeLength);
	DOREPLIFETIME(AMyGameState, team1points);
	DOREPLIFETIME(AMyGameState, team2points);
};

int32 AMyGameState::GetStateTimeleft()
{
	return stateTimeLength - stateTimeElapsed;
}

int32 AMyGameState::GetGameTimeleft()
{
	return gameTimeLength - gameTimeElapsed;
}

int32 AMyGameState::GetStateTimeElapsed()
{
	return stateTimeElapsed;
}

int32 AMyGameState::GetGameTimeElapsed()
{
	return gameTimeElapsed;
}

int32 AMyGameState::GetStateTimeLength()
{
	return stateTimeLength;
}

int32 AMyGameState::GetGameTimeLength()
{
	return gameTimeLength;
}

void AMyGameState::AddTeamPoints(AMyPlayerController* player, int32 amount)
{
	AMyPlayerState* playerState = Cast<AMyPlayerState>(player->PlayerState);
	if (playerState != NULL)
	{
		int32 team = playerState->GetTeam();
		switch (team)
		{
		case 1:
			team1points += amount;
			break;
		case 2:
			team2points += amount;
			break;
		default:
			break;
		}

	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "PlayerState is not correct in team point addition!");
}