// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "MyGameModeTeamRace.h"
#include "MyGameState.h"
#include "PlayerCarCode.h"
#include "MyPlayerState.h"
#include "Util.h"
#include "MyPlayerController.h"


AMyGameModeTeamRace::AMyGameModeTeamRace(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	minPlayersToStart = 4;

	teamRaceRounds = 3;
	teamRaceRoundLength = 5;
	teamRaceRoundFreezeLength = 5;

	//Why is this set this way?
	teamRaceTotalLength = teamRaceTotalLength = ((teamRaceRoundLength + teamRaceRoundFreezeLength) * teamRaceRounds);
}

#if WITH_EDITOR
void AMyGameModeTeamRace::PostEditChangeProperty(FPropertyChangedEvent& propertyChangedEvent)
{
	if (propertyChangedEvent.Property != NULL)
	{
		FName propertyName = propertyChangedEvent.Property->GetFName();
		if (propertyName == GET_MEMBER_NAME_CHECKED(AMyGameModeTeamRace, teamRaceRounds) ||
			propertyName == GET_MEMBER_NAME_CHECKED(AMyGameModeTeamRace, teamRaceRoundLength) ||
			propertyName == GET_MEMBER_NAME_CHECKED(AMyGameModeTeamRace, teamRaceRoundFreezeLength)) 
		{
			teamRaceTotalLength = ((teamRaceRoundLength + teamRaceRoundFreezeLength) * teamRaceRounds);
		}
	}

	Super::PostEditChangeProperty(propertyChangedEvent);
}
#endif

FString AMyGameModeTeamRace::GetTeamRaceStateAsString(InGameState state)
{
	const UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, STRINGIFY(InGameState), true);
	if (enumptr == NULL)
	{
		return FString("Invalid");
	}
	return enumptr->GetEnumName((uint8)state);
}

//void AMyGameModeTeamRace::HandleMatchIsWaitingToStart()
//{
//	Super::HandleMatchIsWaitingToStart();
//}


void AMyGameModeTeamRace::OnMatchStart_Implementation()
{
	Super::OnMatchStart_Implementation();

	teamRaceElapsed = -1;
	GetWorld()->GetTimerManager().SetTimer(teamRaceTimerHandle, this, &AMyGameModeTeamRace::TeamRaceTickSecond, 1.0f, true, 0.0f);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("GameMode: TeamRace"));
}

//TODO: Check if something is needed here
void AMyGameModeTeamRace::Logout(AController* exiting)
{
	//AMyPlayerController* pc = Cast<AMyPlayerController>(exiting);

	Super::Logout(exiting);
}

void AMyGameModeTeamRace::SetupNewPlayer(APlayerController* newPlayer)
{
	Super::SetupNewPlayer(newPlayer);

	AMyPlayerController* pc = Cast<AMyPlayerController>(newPlayer);
	if (pc == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Error: PlayerController is not MyPlayerController"));
		return;
	}
}

void AMyGameModeTeamRace::TeamRaceTickSecond()
{
	teamRaceElapsed++;
	
}

void AMyGameModeTeamRace::UpdateGameState()
{
	Super::UpdateGameState();

	AMyGameState* gameState = Cast<AMyGameState>(GameState);
	if (gameState != NULL)
	{
		gameState->teamRaceState = this->teamRaceState;
		gameState->gameTimeElapsed = teamRaceElapsed;
		gameState->gameTimeLength = teamRaceTotalLength;
		gameState->teamRaceTotalRounds = teamRaceRounds;
		gameState->teamRaceCurrentRound = teamRaceCurrentRound;
		if (teamRaceState == TeamRaceState::Freeze)
		{
			gameState->stateTimeElapsed = teamRaceFreezeElapsed;
			gameState->stateTimeLength = teamRaceRoundFreezeLength;
		}
		else
		{
			gameState->stateTimeElapsed = teamRaceRoundElapsed;
			gameState->stateTimeLength = teamRaceRoundLength;
		}
		if (inGameState != InGameState::Running)
		{
			gameState->stateTimeLength = waitElapsed;
			gameState->teamRaceCurrentRound = 0;
		}

	}
}