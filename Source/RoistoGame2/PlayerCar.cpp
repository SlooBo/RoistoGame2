// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "PlayerCar.h"


// Sets default values
APlayerCar::APlayerCar(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root component is box because car
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxComponent->SetVisibility(true);

	//TODO: Box collision presets
	BoxComponent->SetCollisionProfileName(TEXT("Pawn"));
	//Dont set mesh in code
	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMesh->AttachTo(RootComponent);
	UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(),
		NULL, TEXT("StaticMesh'/Game/Models/Bullets/nuclearBomb.nuclearBomb'")));
	if (CarMesh && meshToUse)
	{
		CarMesh->SetStaticMesh(meshToUse);
	}
	//TODO: Find a proper way to set mesh
	



	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	//TODO: Adjust values
	SpringArm->AttachTo(RootComponent);
	SpringArm->RelativeRotation = FRotator(-20.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 2.0f;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	// Create an instance of our movement component, and tell it to update our root component.
	MyMovementComponent = CreateDefaultSubobject<UCarMovementComponent>(TEXT("CustomMovementComponetn"));
	MyMovementComponent->UpdatedComponent = RootComponent;
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

	//InputComponent->BindAction("Shoot",IE_Pressed,this,&APlayerCar::);

	InputComponent->BindAxis("MoveForward", this, &APlayerCar::MoveForward);
	InputComponent->BindAxis("TurnRight", this, &APlayerCar::Turn);

}

UPawnMovementComponent* APlayerCar::GetMovementComponent() const
{
	return MyMovementComponent;
}

void APlayerCar::MoveForward(float AxisValue)
{
	if (MyMovementComponent && (MyMovementComponent->UpdatedComponent == RootComponent))
	{
		MyMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void APlayerCar::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}
