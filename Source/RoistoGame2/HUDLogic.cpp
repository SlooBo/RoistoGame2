// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "HUDLogic.h"

#include "PlayerCarCode.h"
#include "MyPlayerState.h"
#include "Util.h"
#include "MyGameState.h"

UHUDLogic::UHUDLogic()
{

}
UHUDLogic::~UHUDLogic()
{

}

void UHUDLogic::SetUp(UUserWidget* widget, UWorld *world)
{
	this->baseWidget = widget;
	this->world = world;

	//SetValueFromWidget(&raceTimeLeft, "RaceTimer");
	SetValueFromWidget(&raceTimeLeft, "RoundTimer");
	SetValueFromWidget(&currentRoundText, "Round");
	SetValueFromWidget(&team1Points, "Team1Points");
	SetValueFromWidget(&team2Points, "Team2Points");
	SetValueFromWidget(&cashText, "Money");
}

void UHUDLogic::Update()
{
	APlayerCarCode *player = Cast<APlayerCarCode>(world->GetFirstPlayerController()->GetPawn());
	if (player == nullptr)
		return;


	AMyGameState *gameState = Cast<AMyGameState>(world->GameState);
	if (gameState != nullptr)
	{
		FText text = FText::FromString(FString::FromInt(gameState->GetStateTimeleft()));

		raceTimeLeft->SetText(text);

		currentRoundText->SetText(FText::FromString(FString::FromInt(gameState->GetTeamRaceCurrentRound() + 1)));
		
		team1Points->SetText(FText::FromString(FString::FromInt(gameState->GetTeam1Points())));
		team2Points->SetText(FText::FromString(FString::FromInt(gameState->GetTeam2Points())));
	}

	AMyPlayerState* playerState = Cast<AMyPlayerState>(world->GetFirstPlayerController()->PlayerState);
	if (playerState != NULL)
	{
		cashText->SetText(FText::FromString(FString::FromInt(playerState->GetMoney()) + " $"));
	}
}