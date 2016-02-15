// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "UnrealNetwork.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"
#include "PlayerCarCode.h"
#include "PlayerHUD.h"
#include "MyGameMode.h"


AMyPlayerController::AMyPlayerController(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	bReplicates = true;


}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, canBuild);
	DOREPLIFETIME(AMyPlayerController, isBuilding);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//TODO: Add music playing here
	//only play music for clienst

	//TODO: Add HUD here
	/*APlayerHud *hud = Cast<APlayerHud>(GetHUD());
	if (hud != nullptr)
		hud->changeUIElement(MenuType::GAME_UI);*/
}

void AMyPlayerController::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	//TODO: below lines
	/*musicComponent->OnAudioFinished.RemoveDynamic(this, &ACMPlayerController::MusicPlay);
	musicComponent->Stop();*/

	Super::EndPlay(endPlayReason);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("AllChat", IE_Pressed, this, &AMyPlayerController::OpenAllChat);
	InputComponent->BindAction("TeamChat", IE_Pressed, this, &AMyPlayerController::OpenTeamChat);
}

void AMyPlayerController::TryRespawn()
{
	if (IsAlive())
		return;

	RequestRespawn();
}

bool AMyPlayerController::RequestRespawn_Validate()
{
	return true;
}

void AMyPlayerController::RequestRespawn_Implementation()
{
	AMyGameMode* gameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode != NULL)
	{
		if (gameMode->CanPlayerRespawn(this))
			gameMode->RespawnPlayer(this);
	}
}

void AMyPlayerController::Possess(APawn* inPawn)
{
	Super::Possess(inPawn);

	if (!HasAuthority())
		return;

	APlayerCarCode* pc = Cast<APlayerCarCode>(inPawn);
	//ABuildChar* builder = Cast<>(inPawn);
	if (pc != NULL /*&& builder == NULL*/)
	{
		//handle APlayerCarCode possession here
	}
	//else if (builder != NULL)
	//{
	//	//handle builder character possession here
	//}

}

void AMyPlayerController::UnPossess()
{
	APlayerCarCode* pc = Cast<APlayerCarCode>(GetPawn());
	//ABuildChar* builder = Cast<>(GetPawn());
	if (pc != NULL /*&& builder == NULL*/)
	{
		//handle APlayerCarCode unpossession here
	}
	//else if (builder != NULL)
	//{
	//	//handle builder character unpossession here
	//}

	Super::UnPossess();
}

void AMyPlayerController::OnPlayerDeath()
{

}

void AMyPlayerController::OnPlayerDeathBroadcast_Implementation(AMyPlayerController* killed, AMyPlayerController* killer/*, AWeapon* weapon*/)
{
	if (killed == this)
	{
		/*APlayerHud* hud = Cast<APlayerHUD>(GetHUD());
		if (hud != nullptr)
		{
			hud->ShowText("After 5 seconds press R to respawn", 32, 0.5f, 0.05f, 10, FLinearColor::Red);
			hud->ShowText("Press B to open shop", 32, 0.5f, 0.95f, 10, FLinearColor::Red);
		}*/
		//handle clientside death here
	}
	// handle kill messages and other death related stuff here
}

void AMyPlayerController::OnMatchStart_Implementation()
{

}

void AMyPlayerController::OnWarmupStart_Implementation()
{

}

bool AMyPlayerController::IsAlive()
{
	AMyPlayerState *playerState = Cast<AMyPlayerState>(PlayerState);
	if (playerState != NULL)
		return playerState->IsAlive();
	return false;
}

void AMyPlayerController::OpenTeamChat()
{

}

void AMyPlayerController::OpenAllChat()
{

}