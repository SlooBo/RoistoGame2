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
	SetValueFromWidget(&currentRoundText, "RoundTimer");
	SetValueFromWidget(&currentRoundText, "Team1Points");
	SetValueFromWidget(&currentRoundText, "Team2Points");
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

		//currentRoundText->SetText(FText::FromString(FString::FromInt(gameState->GetTeamRaceCurrentRound() + 1)));
		
	
	}
}