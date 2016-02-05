// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyPlayerController(const class FObjectInitializer& objectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Reliable, Client)
	void OnMatchStart();

	UFUNCTION(Reliable, Client)
	void OnWarmupStart();
	
protected:

	UPROPERTY(REPLICATED)
	bool canBuild;

	UPROPERTY(REPLICATED)
	bool isBuilding;
};
