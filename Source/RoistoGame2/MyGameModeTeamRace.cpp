// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "MyGameModeTeamRace.h"
#include "PlayerCarCode.h"
#include "MyPlayerState.h"
#include "Util.h"
#include "MyPlayerController.h"


AMyGameModeTeamRace::AMyGameModeTeamRace(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	//Defaults for game mode, use blueprints to override

	//Here be the final blueprinted player class
	/*static ConstructorHelpers::FObjectFinder<UBlueprint> APlayerCarCode(TEXT(""));
	if (APlayerCarCode.Object)
	DefaultPawnClass = (UClass*)APlayerCarCode.Object->GeneratedClass;*/

	//Here be the final blueprinted Hud class
	/*static ConstructorHelpers<UBlueprint> PlayerHud(TEXT(""));
	if (PlayerHud.Object)
	HUDClass = (UClass*)PlayerHud.Object->GeneratedClass;*/

	//PlayerControllerClass = AMyPlayerController::StaticClass();
	/*PlayerStateClass = AMyPlayerState::StaticClass();
	SpectatorClass =
	GhostCharacterClass =
	GameStateClass =*/

	DefaultPlayerName = FText::FromString("FastCar");

	//TODO: Check true functioning behind this
	bDelayedStart = true;

	startTime = 0;
	warmupTime = 0;
	//Again, set in blueprint
	playerStartMoney = 1000;
	playerMaxMoney = 2000;
	playerReward = 500;

}

FString AMyGameModeTeamRace::GetInGameStateAsString(InGameState state)
{
	const UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, STRINGIFY(InGameState), true);
	if (enumptr == NULL)
	{
		return FString("Invalid");
	}
	return enumptr->GetEnumName((uint8)state);
}

void AMyGameModeTeamRace::StartNewPlayer(APlayerController* newPlayer)
{
	SetupNewPlayer(newPlayer);

	Super::StartNewPlayer(newPlayer);
}

void AMyGameModeTeamRace::Logout(AController* exiting)
{
	AMyPlayerController* pc = Cast<AMyPlayerController>(exiting);

	// remove ongoing respawn timers if player disconnects
	if (pc != NULL && respawnTimerList.Contains(pc))
		GetWorld()->GetTimerManager().ClearTimer(respawnTimerList[pc]);

	Super::Logout(exiting);
}

//TODO:Check if this needed
void AMyGameModeTeamRace::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	inGameState = InGameState::WarmupStarting;

	waitElapsed = -1;
	GetWorld()->GetTimerManager().SetTimer(waitTimer, this, &AMyGameModeTeamRace::WaitTickSecond, 1.0f, true, 0.0f);
}

void AMyGameModeTeamRace::StartMatch()
{
	if (inGameState != InGameState::Warmup)
		MatchState = MatchState::WaitingToStart;

	Super::StartMatch();

	if (inGameState == InGameState::Warmup)
	{
		OnWarmupStart();
		return;
	}

	//GetWorld()->GetTimerManager().ClearTimer(waitTimer);

	// match needs restarting, move players back to spawn
	for (auto iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{
		if ((*iter)->GetPawn() != NULL)
			(*iter)->GetPawn()->Reset();

		AMyPlayerState* playerState = Cast<AMyPlayerState>((*iter)->PlayerState);
		if (playerState != NULL)
			playerState->ResetStats();

		RespawnPlayer(*iter);
	}

	mapTimeElapsed = 0;
	GetWorld()->GetTimerManager().SetTimer(mapTimerHandle, this, &AMyGameModeTeamRace::MapTickSecond, 1.0f, true);

	OnMatchStart();
}
bool AMyGameModeTeamRace::ShouldSpawnAtStartSpot(AController* player)
{
	//TODO: Check what relation this has with controller location
	//do not reuse the same spawn point for every spawn
	return false;
}

//TODO: make this sensible
AActor* AMyGameModeTeamRace::ChoosePlayerStart_Implementation(AController* player)
{
	AActor* spawnLocation = NULL;

	if (respawnMode == RespawnMode::AtBuilder)
	{
		APlayerController* playerController = player->CastToPlayerController();
		if (playerController != NULL)
		{
			spawnLocation = playerController->GetPawnOrSpectator();
			//if (spawnLocation == NULL)
			//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Warning: Unable to get ghost/spectator pawn, choosing best spawn point instead"));
		}
	}

	if (respawnMode == RespawnMode::AtSpawnPoint)
	{
		//spawnLocation = GetRandoSpawnPoint(player);
		/*if (spawnLocation == NULL)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Error: No spawn points were found, add PlayerStart to level"));*/
	}

	return spawnLocation;
}

void AMyGameModeTeamRace::SetPlayerDefaults(APawn* playerPawn)
{
	APlayerCarCode* playerCar = Cast<APlayerCarCode>(playerPawn);
	if (playerCar == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Error: SetPlayerDefaults player pawn is not PlayerCharacter"));
		return;
	}

	//setup character here
	AMyPlayerController* player = Cast<AMyPlayerController>(playerCar->GetController());
	if (player == NULL)
		return;

	AMyPlayerState* playerState = Cast<AMyPlayerState>(player->PlayerState);
	if (playerState == NULL)
		return;


	playerState->SetAlive(true);
}

void AMyGameModeTeamRace::RestartPlayer(AController* controller)
{
	AMyPlayerController* player = Cast<AMyPlayerController>(controller->CastToPlayerController());
	if (player == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Error: RestartPlayer, controller is not MyPlayerController"));
		return;
	}

	//// clear respawn timers if player respawned early
	//if (respawnTimerList.Contains(player))
	//	GetWorld()->GetTimerManager().ClearTimer(respawnTimerList[player]);

	if (player->PlayerState == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Error: RestartPlayer, PlayerState is null (player disconnected?)"));
		return;
	}

	//TODO: Check this part!
	APlayerCarCode* playerCar = Cast<APlayerCarCode>(player->GetPawn());
	//TODO: add here buildPawn???
	if (playerCar != NULL)
	{
		//do nothing if player is already driving
		return;
	}

	//create and place player pawn
	AActor* startPos = FindPlayerStart(player);
	APawn* newPawn = SpawnDefaultPawnFor(player, startPos);
	if (newPawn == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Error: SetPlayerDefaults player pawn is not PlayerCharacter"));
		//SpectatePlayer(player);
		return;
	}

	/*if (buildCharacter != NULL)
	{
	buildCharacter->SetActorHiddenInGame(true);
	buildCharacter->SetActorEnableCollision(false);
	buildCharacter->SetActorTickEnabled(false);
	}*/

	//check if this line is needed
	player->PlayerState->bIsSpectator = false;
	player->ChangeState(NAME_Playing);
	player->ClientGotoState(NAME_Playing);

	FRotator NewControllerRot = startPos->GetActorRotation();
	NewControllerRot.Roll = 0.f;
	/*if (buildCharacter != NULL)
	NewControllerRot.Pitch = buildCharacter->GetControlRotation().Pitch;*/

	player->UnPossess();
	player->SetPawn(newPawn);
	player->Possess(newPawn);

	player->SetControlRotation(NewControllerRot);

	SetPlayerDefaults(newPawn);

	/*if (buildCharacter != NULL)
	buildCharacter->Destroy();*/

	AllowPlayerRespawn(player);

	OnPlayerRespawn(player);
}

void AMyGameModeTeamRace::WaitTickSecond()
{

}

void AMyGameModeTeamRace::MapTickSecond()
{
	mapTimeElapsed++;

	if (mapTimelimit > 0 && inGameState != InGameState::Starting)
	{
		if (mapTimeElapsed >= mapTimelimit)
		{
			mapTimeElapsed = 0;
			//OnMapTimeout();
		}
		else
		{
			//TODO: notify players to display timeleft messages?
		}
	}
	//UpdateGameState();
}

int32 AMyGameModeTeamRace::MapTimeleft()
{
	return (mapTimelimit > 0) ? (mapTimelimit - mapTimeElapsed) : 0;
}

int32 AMyGameModeTeamRace::MapTimeElapsed()
{
	return mapTimeElapsed;
}

bool AMyGameModeTeamRace::CanPlayerRespawn(APlayerController* player)
{
	AMyPlayerState* playerState = Cast<AMyPlayerState>(player->PlayerState);
	if (playerState != NULL && !playerState->IsAlive() && !denyRespawnList.Contains(player))
		return true;
	return false;
}

void AMyGameModeTeamRace::AllowPlayerRespawn(APlayerController* player)
{
	if (denyRespawnList.Contains(player))
		denyRespawnList.Remove(player);
}

void AMyGameModeTeamRace::RespawnPlayer(APlayerController* player, float respawnDelay)
{
	if (player == NULL)
		return;

	if (respawnDelay <= 0.0f)
	{
		RestartPlayer(player);
		return;
	}

	if (!respawnTimerList.Contains(player))
	{
		FTimerHandle timerHandle;
		respawnTimerList.Add(player, timerHandle);
	}

	//From different project;Might not be needed in this game
	//FTimerDelegate respawnDelegate = FTimerDelegate::CreateUObject<ACMGameMode, AController*>(this, &ACMGameMode::RestartPlayer, player);
	//GetWorld()->GetTimerManager().SetTimer(respawnTimerList[player], respawnDelegate, respawnDelay, false);
}

void AMyGameModeTeamRace::OnMatchStart_Implementation()
{
	for (TActorIterator<AMyPlayerController> iter(GetWorld()); iter; ++iter)
	{
		SetupNewPlayer(*iter);
		//TODO!!!:MyPlayerController
		(*iter)->OnMatchStart();
	}
}

void AMyGameModeTeamRace::SetupNewPlayer(APlayerController* newPlayer)
{
	AMyPlayerState* playerState = Cast<AMyPlayerState>(newPlayer->PlayerState);
	if (playerState != NULL)
	{
		if (inGameState == InGameState::Warmup)
			playerState->SetMoney(playerMaxMoney);
		else
			playerState->SetMoney(playerStartMoney);
	}
}

//TODO: this
void AMyGameModeTeamRace::OnPlayerRespawn_Implementation(AMyPlayerController* player)
{
	/*for (TActorIterator<ABuilderCharacter> iter(GetWorld()); iter; ++iter)
	(*iter)->SetPlayerVisibility(false);*/
}

void AMyGameModeTeamRace::OnWarmupStart_Implementation()
{
	for (TActorIterator<AMyPlayerController> iter(GetWorld()); iter; ++iter)
	{
		SetupNewPlayer(*iter);
		(*iter)->OnWarmupStart();
	}
}
