// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "MyPlayerState.h"
#include "UnrealNetwork.h"

AMyPlayerState::AMyPlayerState(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	alive = false;
	bReplicates = true;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMyPlayerState, alive);
	DOREPLIFETIME(AMyPlayerState, team);
	DOREPLIFETIME(AMyPlayerState, money);
}

void AMyPlayerState::ResetStats()
{
	money = 0;
}

int32 AMyPlayerState::GetTeam()
{
	return team;
}

void AMyPlayerState::SetTeam(int32 newTeam)
{
	team = newTeam;
}

int32 AMyPlayerState::GetMoney()
{
	return money;
}

void AMyPlayerState::AddMoney(int32 num)
{
	SetMoney(money + num);
}

void AMyPlayerState::SetMoney(int32 num)
{
	int32 maxMoney = MAX_int32;
	AMyGameMode* gameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode != NULL)
		maxMoney = gameMode->GetPlayerMaxMoney();

	money = num;
	if (money < 0)
		money = 0;

	if (money > maxMoney)
		money = maxMoney;
}

bool AMyPlayerState::IsAlive()
{
	return alive;
}

void AMyPlayerState::SetAlive(bool alive)
{
	this->alive = alive;
}