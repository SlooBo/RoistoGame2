// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define STRINGIFY(str) L#str

/**
 * 
 */
class ROISTOGAME2_API Util
{
public:
	Util();
	~Util();

	static class APlayerCar* GetLocalPlayer(UWorld* world);
	static class APlayerCar* GetPlayerCar(APlayerController* player);
	static int32 GetNumPlayers(UWorld* world);

};
