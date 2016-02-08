// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "UnrealNetwork.h"
#include "MyPlayerController.h"
#include "MyPlayerState.h"


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

	//RequestRespawn();
}



void AMyPlayerController::Possess(APawn* inpPawn)
{

}

void AMyPlayerController::UnPossess()
{

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