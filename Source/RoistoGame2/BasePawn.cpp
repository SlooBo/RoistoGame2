// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "BasePawn.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABasePawn::DelayedDestroy()
{
	FTimerHandle timerHandle;
	FTimerDelegate destroyDelegate = FTimerDelegate::CreateUObject<ABasePawn, FTimerHandle&>(this, &ABasePawn::DelayedDestroy, timerHandle);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, destroyDelegate, 1.0f, true);

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void ABasePawn::OnDeath_Implementation(AMyplayerController* damageSource)
{
	// delay the destruction until the player controller no longer controls this character
	// if pawn is destroyed before the controller acknowledges it, crash happens

	DelayedDestroy();
}


void ABasePawn::DelayedDestroy(FTimerHandle& timerHandle)
{
	if (Controller == NULL)
	{
		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
		Destroy(true);
	}
}
