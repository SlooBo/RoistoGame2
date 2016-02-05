// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "UnrealNetwork.h"
#include "MyPlayerController.h"


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

void AMyPlayerController::OnMatchStart_Implementation()
{

}

void AMyPlayerController::OnWarmupStart_Implementation()
{

}