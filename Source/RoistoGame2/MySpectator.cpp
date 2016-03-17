// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "MySpectator.h"
#include "MyPlayerController.h"


AMySpectator::AMySpectator(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void AMySpectator::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Try_respawn", IE_Pressed, this, &AMySpectator::TryRespawn);
}


void AMySpectator::TryRespawn()
{
	AMyPlayerController* playerController = Cast<AMyPlayerController>(GetController());
	if (playerController != NULL)
		playerController->RequestRespawn();
}