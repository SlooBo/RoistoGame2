// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "MyGameMode.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMyPlayerState(const FObjectInitializer& objectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	/************************************************************************/
	/* Core States                                                          */
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Reset Player States"), Category = "Gameplay")
	void ResetStats();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Get Team Number"), Category = "Gameplay")
	int32 GetTeam();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Set Team Number"), Category = "Gameplay")
	void SetTeam(int32 newTeam);

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Is Alive"), Category = "Gameplay")
	bool IsAlive();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Set Alive"), Category = "Gameplay")
	void SetAlive(bool alive);

	/************************************************************************/
	/* Ca$h                                                                 */
	/************************************************************************/

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Get Money"), Category = "Gameplay")
	int32 GetMoney();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Get Lap"), Category = "Gameplay")
	int32 GetLap();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Add Money"), Category = "Gameplay")
	void AddMoney(int32 num);

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Set Money"), Category = "Gameplay", Exec)
	void SetMoney(int32 num);

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Add lap"), Category = "Gameplay")
	void AddLap();
	
protected:

	//Is alive
	UPROPERTY(Replicated)
	bool alive;

	// 0 = No Team, 1-4 = Teams
	UPROPERTY(Replicated, EditAnywhere, Meta = (DisplayName = "Team Number", ClampMin = "0", UIMin = "0"))
	int32 team;

	// Player Money
	UPROPERTY(Replicated, Meta = (DisplayName = "Player Money", ClampMin = "0"))
	int32 money;

	UPROPERTY(VisibleAnywhere, Replicated, Meta = (DisplayName = "Player laps", ClampMin = "0"))
	int32 lap;
	
};
