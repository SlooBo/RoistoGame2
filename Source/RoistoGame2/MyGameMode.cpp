// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "MyGameMode.h"
#include "PlayerCar.h"
#include "Util.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	//Defaults for game mode, use blueprints to override

	//Here be the final blueprinted player class
	/*static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerCar(TEXT(""));
	if (PlayerCar.Object)
		DefaultPawnClass = (UClass*)PlayerCar.Object->GeneratedClass;*/

	//Here be the final blueprinted Hud class
	/*static ConstructorHelpers<UBlueprint> PlayerHud(TEXT(""));
	if (PlayerHud.Object)
		HUDClass = (UClass*)PlayerHud.Object->GeneratedClass;*/
	
	//PlayerControllerClass = AMyPlayerController::StaticClass();
	/*PlayerStateClass = 
	SpectatorClass =
	GhostCharacterClass =
	GameStateClass =*/
	
	//DefaultPlayerName = FText::FromString("FastCar");

	//TODO: Check true functioning behind this
	bDelayedStart = true;

	startTime = 0;
	warmupTime = 0;
	//Again, set in blueprint
	playerStartMoney = 1000;
	playerMaxMoney = 2000;
	playerReward = 500;

}

FString AMyGameMode::GetInGameStateAsString(InGameState state)
{
	const UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, STRINGIFY(InGameState), true);
	if (enumptr == NULL)
	{
		return FString("Invalid");
	}
	return enumptr->GetEnumName((uint8)state);
}

bool AMyGameMode::ShouldSpawnAtStartSpot(AController* player)
{
	//TODO: Check what relation this has with controller location
	//do not reuse the same spawn point for every spawn
	return false;
}

//TODO: make this sensible
AActor* AMyGameMode::ChoosePlayerStart_Implementation(AController* player)
{
	AActor* spawnLocation = NULL;

	if (respawnMode == RespawnMode::AtGhost)
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

//void AMyGameMode::OnMatchStart_Implementation()
//{
//	for (TActorIterator<AMyPlayerController> iter(GetWorld()); iter; ++iter)
//	{
//		SetupNewPlayer(*iter);
//		//TODO!!!:MyPlayerController
//		(*iter)->OnMatchStart();
//	}
//}

void AMyGameMode::SetupNewPlayer(APlayerController* newPlayer)
{
	/*ACMPlayerState* playerState = Cast<ACMPlayerState>(newPlayer->PlayerState);
	if (playerState != NULL)
	{
		if (inGameState == InGameState::Warmup)
			playerState->SetMoney(playerMaxMoney);
		else
			playerState->SetMoney(playerStartMoney);
	}*/
}

//void AMyGameMode::RespawnPlayer(APlayerController* player, float respawnDelay)
//{
//	if (player == NULL)
//		return;
//
//	if (respawnDelay <= 0.0f)
//	{
//		//RestartPlayer(player);
//		return;
//	}
//
//	if (!respawnTimerList.Contains(player))
//	{
//		FTimerHandle timerHandle;
//		respawnTimerList.Add(player, timerHandle);
//	}
//
//	//From different project;Might not be needed in this game
//	//FTimerDelegate respawnDelegate = FTimerDelegate::CreateUObject<ACMGameMode, AController*>(this, &ACMGameMode::RestartPlayer, player);
//	//GetWorld()->GetTimerManager().SetTimer(respawnTimerList[player], respawnDelegate, respawnDelay, false);
//}

void AMyGameMode::StartNewPlayer(APlayerController* newPlayer)
{
	SetupNewPlayer(newPlayer);

	Super::StartNewPlayer(newPlayer);
}

void AMyGameMode::Logout(AController* exiting)
{
	AMyPlayerController* pc = Cast<AMyPlayerController>(exiting);

	// remove ongoing respawn timers if player disconnects
	if (pc != NULL && respawnTimerList.Contains(pc))
	GetWorld()->GetTimerManager().ClearTimer(respawnTimerList[pc]);

	Super::Logout(exiting);
}

//TODO:Check
void AMyGameMode::HandleMatchIsWaitingToStart()
{
	//Super::HandleMatchIsWaitingToStart();

	//inGameState = InGameState::WarmupStarting;

	////waitElapsed = -1;
	//GetWorld()->GetTimerManager().SetTimer(waitTimer, this, &AMyGameMode::WaitTickSecond, 1.0f, true, 0.0f);
}

void AMyGameMode::StartMatch()
{
	//if (inGameState != InGameState::Warmup)
	//	MatchState = MatchState::WaitingToStart;

	//Super::StartMatch();

	//if (inGameState == InGameState::Warmup)
	//{
	//	OnWarmupStart();
	//	return;
	//}

	//GetWorld()->GetTimerManager().ClearTimer(waitTimer);

	//// match needs restarting, move players back to spawn
	//for (auto iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	//{
	//	if ((*iter)->GetPawn() != NULL)
	//		(*iter)->GetPawn()->Reset();

	//	ACMPlayerState* playerState = Cast<ACMPlayerState>((*iter)->PlayerState);
	//	if (playerState != NULL)
	//		playerState->ResetStats();

	//	RespawnPlayer(*iter);
	//}

	//mapTimeElapsed = 0;
	//GetWorld()->GetTimerManager().SetTimer(mapTimerHandle, this, &ACMGameMode::MapTickSecond, 1.0f, true);

	//OnMatchStart();
}