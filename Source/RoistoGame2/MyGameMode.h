// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

UENUM(BlueprintType)
enum class InGameState : uint8
{
	WarmupStarting,
	Warmup,
	Starting,
	Running,
	End,
};

//This is test version and will not be in the final version
UENUM(BlueprintType)
enum class RespawnMode : uint8
{
	// Default mode, spawns at random (team) spawn point
	AtSpawnPoint = 0,

	// Player may spawn at ghost location
	AtBuilder,

	// Player may spawn at ghost location, but is placed to random spawn point after death
	AtBuilderNearSpawn,
};
/**
 * 
 */
UCLASS()
class ROISTOGAME2_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMyGameMode(const class FObjectInitializer& objectInitializer);

	static FString GetInGameStateAsString(InGameState state);
	InGameState GetInGameState() { return inGameState; };
	
	//Overrides
	virtual void StartNewPlayer(APlayerController* newPlayer) override;
	virtual void Logout(AController* exiting) override;
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void StartMatch() override;

	virtual bool ShouldSpawnAtStartSpot(AController* player) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* player) override;
	virtual void SetPlayerDefaults(APawn* playerPawn) override;
	virtual void RestartPlayer(AController* controller) override;

	//virtual void UpdateGameState();

	void WaitTickSecond();
	void MapTickSecond();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Map Time Left"), Category = "Gameplay|Level")
	int32 MapTimeleft();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Map Time Elapsed"), Category = "Gameplay|Level")
	int32 MapTimeElapsed();

	//Returns bool can player respawn
	virtual bool CanPlayerRespawn(APlayerController* player);
	//Changes player to be able to respawn
	void AllowPlayerRespawn(APlayerController* player);

	//Respawns player
	UFUNCTION(BlueprintCallable, Meta = (Displayname = "Respawn Player"), Category = "Gameplay|Player")
	void RespawnPlayer(APlayerController* player, float respawnDelay = 0.0f);

	//Event when match has started
	UFUNCTION(BlueprintNativeEvent, Meta = (DisplayName = "On Match Start"), Category = "Gameplay")
	void OnMatchStart();
	virtual void OnMatchStart_Implementation();


	virtual void SetupNewPlayer(APlayerController* newPlayer);

	//UFUNCTION(BlueprintNativeEvent, Meta = (DisplayName = "On Player Death"), Category = "Gameplay|Player")
	//// Event when player dies or is killed by other player, called by the player
	//void OnPlayerDeath(AMyPlayerController* player, AMyPlayerController* killer = NULL);
	//virtual void OnPlayerDeath_Implementation(AMyPlayerController* player, AMyPlayerController* killer = NULL);

	// Event when player respawns
	UFUNCTION(BlueprintNativeEvent, Meta = (DisplayName = "On Player Respawn"), Category = "Gameplay|Player")
	void OnPlayerRespawn(AMyPlayerController* player);
	virtual void OnPlayerRespawn_Implementation(AMyPlayerController* player);

	// Event when warmup has started
	UFUNCTION(BlueprintNativeEvent, Meta = (DisplayName = "On Warmup Start"), Category = "Gameplay")
	void OnWarmupStart();
	virtual void OnWarmupStart_Implementation();

	int32 GetPlayerMaxMoney() { return playerMaxMoney; };

protected:

	TArray<APlayerController*> denyRespawnList;
	TMap<APlayerController*, FTimerHandle> respawnTimerList;

	// Timelimit in minutes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Map Timelimit", ClampMin = "0"), Category = "Gameplay|Level")
	int32 mapTimelimit;

	int32 mapTimeElapsed;
	int32 waitElapsed;

	FTimerHandle mapTimerHandle;	// Ticks once every second when the main game mode is running
	FTimerHandle waitTimer;			// Wait for players timer before game starts

	//Current state of the game mode
	UPROPERTY(BluePrintReadOnly, Category = Enum)
	InGameState inGameState;

	// Respawning mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Respawn Mode"), Category = Enum)
	RespawnMode respawnMode;

	// Time to wait before game mode starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Start Delay Time", ClampMin = "0"), Category = "Gameplay|Level")
	int32 startTime;

	// Max Length of warmup while waiting for players to join
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Warmup Time", ClampMin = "0"), Category = "Gameplay|Level")
	int32 warmupTime;

	// Player respawn time after death (-1: respawning disabled)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Player Respawn Time", ClampMin = "-1"), Category = "Gameplay|Level")
	int32 playerRespawnTime;

	//
	//	Money / Kill Rewards
	//

	// Start money for each player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Player Start Money"), Category = "Gameplay|Money")
		int32 playerStartMoney;

	// Limit maximum money players can have
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Player Max Money"), Category = "Gameplay|Money")
		int32 playerMaxMoney;

	// Reward for stuff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Player Kill Reward Target"), Category = "Gameplay|Money")
		int32 playerReward;
};
