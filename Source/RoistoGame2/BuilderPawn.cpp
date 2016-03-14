// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "BuilderPawn.h"


ABuilderPawn::ABuilderPawn(const FObjectInitializer& ObjectInitializer)
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
	/* Don't collide with camera checks to keep 3rd person camera at position when other players between pawn and camera */
	MyHitBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);


	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	//TODO: Adjust values
	SpringArm->AttachTo(RootComponent);
	SpringArm->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 2.0f;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ABuilderPawn::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void ABuilderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABuilderPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//InputComponent->BindAction("Shoot",IE_Pressed,this,&ABuilderPawn::);

}