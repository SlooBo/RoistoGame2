// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class ROISTOGAME2_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Ordinal number of checkpoint", ClampMin = "0", ClampMax = "10"), Category = "Gameplay|Checkpoint")
	int32 ordinal;

	UBoxComponent* MyHitBox;
};
