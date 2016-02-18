// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "Checkpoint.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Root component is box collider
	MyHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = MyHitBox;
	//TODO:Adjust these
	MyHitBox->SetBoxExtent(FVector(500.0f, 100.0f, 500.0f));
	MyHitBox->SetVisibility(true);
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

