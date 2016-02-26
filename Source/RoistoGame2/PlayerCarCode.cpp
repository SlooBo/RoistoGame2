// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "UnrealNetwork.h"
#include "MyPlayerState.h"
#include "PlayerCarCode.h"

// Sets default values
APlayerCarCode::APlayerCarCode(const class FObjectInitializer& ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root component is box because car
	MyHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = MyHitBox;
	MyHitBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	MyHitBox->SetVisibility(true);

	//TODO: Box collision presets
	MyHitBox->SetCollisionProfileName(TEXT("Pawn"));
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

	//set gameplay values
	Checkpoint1 = false;
	Checkpoint2 = false;
	Checkpoint3 = false;

	lap = 0;
}

// Called when the game starts or when spawned
void APlayerCarCode::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCarCode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCarCode::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//InputComponent->BindAction("Shoot",IE_Pressed,this,&PlayerCarCode::);

	InputComponent->BindAxis("MoveForward", this, &APlayerCarCode::MoveForward);
	InputComponent->BindAxis("TurnRight", this, &APlayerCarCode::Turn);
	InputComponent->BindAxis("MoveForwardPad", this, &APlayerCarCode::MoveForward);
	InputComponent->BindAxis("TurnRightPad", this, &APlayerCarCode::Turn);

}

void APlayerCarCode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Value is already updated locally, skip in replication step
	//DOREPLIFETIME_CONDITION(APlayerCharacter, value, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(APlayerCarCode, lap, COND_SkipOwner);

	//Replicated to every client, no special condition required
	//DOREPLIFETIME(APlayerCharacter, value);
}

UPawnMovementComponent* APlayerCarCode::GetMovementComponent() const
{
	return MyMovementComponent;
}

//UBoxComponent* PlayerCarCode::getHitBox()
//{
//	return  MyHitBox;
//}

void APlayerCarCode::MoveForward(float AxisValue)
{
	if (MyMovementComponent && (MyMovementComponent->UpdatedComponent == RootComponent))
	{
		MyMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void APlayerCarCode::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void APlayerCarCode::addCheckpoint(int checkpoint)
{
	switch (checkpoint)
	{
	case 1:
	Checkpoint1 = true;
		break;
	case 2:
		Checkpoint2 = true;
		break;
	case 3:
		Checkpoint3 = true;
		break;
	default:
		break;
	}
}



void APlayerCarCode::addLap()
{
	if (Checkpoint1 && Checkpoint2 && Checkpoint3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, " Survived lap !!!");
		lap++;
		Checkpoint1 = false;
		Checkpoint2 = false;
		Checkpoint3 = false;
		AMyPlayerState* playerState = Cast<AMyPlayerState>(PlayerState);
		if (playerState == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Major error during lap finish!");
			return;
		}
		//TODO:Adjust this
		playerState->AddMoney(500);
	}
}