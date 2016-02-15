// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameMode.h"
#include "BuilderPawn.h"
#include "MyGameModeTeamRace.generated.h"

UENUM(BlueprintType)
enum class TeamRaceState : uint8
{
	Start = 0,
	Freeze,
	Round,
	End,
};

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API AMyGameModeTeamRace : public AMyGameMode
{
	GENERATED_BODY()
public:
	AMyGameModeTeamRace(const class FObjectInitializer& objectInitializer);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& changedEvent) override;
#endif

	static FString GetTeamRaceStateAsString(InGameState state);

	//Overrides
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void OnMatchStart_Implementation() override;
	virtual void Logout(AController* exiting) override;
	virtual void SetupNewPlayer(APlayerController* newPlayer) override;

	//// Event when player dies or is killed by other player
	virtual void OnPlayerDeath_Implementation(AMyPlayerController* player, AMyPlayerController* killer = NULL);

	void TeamRaceTickSecond();

	virtual void UpdateGameState() override;



protected:

	FTimerHandle teamRaceTimerHandle; //Ticks once every second during hunt
	int32 teamRaceElapsed;
	int32 teamRaceCurrentRound;
	int32 teamRaceFreezeElapsed;
	int32 teamRaceRoundElapsed;

	//Current state of the team race
	UPROPERTY(BlueprintReadOnly, Category = Enum)
	TeamRaceState teamRaceState;
	
	//
	//	Round Settings
	//

	//Count of team race round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Teamrace Rounds", ClampMin = "0"), Category = "Gameplay|TeamRace")
	int32 teamRaceRounds;

	// Length of one hunt round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Teamrace Round Length", ClampMin = "0"), Category = "Gameplay|TeamRace")
		int32 teamRaceRoundLength;

	// Freeze time length at the beginning of a round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Teamrace Freeze Time Length", ClampMin = "0"), Category = "Gameplay|TeamRace")
		int32 teamRaceRoundFreezeLength;


	// Total length of hunt match (calculated from previous values)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (DisplayName = "Teamrace Total Length"), Category = "Gameplay|TeamRace")
		int32 teamRaceTotalLength;

	//
	//	Hunt Money / Kill Rewards
	//

	// Money given at the end of round
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Teamrace Round Reward"), Category = "Gameplay|TeamRace")
	int32 teamRaceRoundReward;
};
