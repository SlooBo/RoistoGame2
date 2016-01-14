// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "PlayerCar.h"


// Sets default values
APlayerCar::APlayerCar(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	//TODO: Box collision presets

	//Dont set mesh in code
	UStaticMeshComponent* CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMesh->AttachTo(RootComponent);
	
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->AttachTo(RootComponent);

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlayerCar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

