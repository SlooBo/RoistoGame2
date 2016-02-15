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

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	virtual void SetupInputComponent() override;

	/*UFUNCTION(Reliable, Server, WithValidation)
	void ServerInitInventory();*/

	void TryRespawn();

	UFUNCTION(Reliable, Server, WithValidation)
	void RequestRespawn();

	virtual void Possess(APawn* inPawn) override;
	virtual void UnPossess() override;

	void OnPlayerDeath();

	UFUNCTION(Reliable, Client)
	void OnPlayerDeathBroadcast(AMyPlayerController* killed, AMyPlayerController* killer/*, AWeapon* weapon*/);

	UFUNCTION(Reliable, Client)
	void OnMatchStart();

	UFUNCTION(Reliable, Client)
	void OnWarmupStart();

	bool IsAlive();
	
protected:

	UPROPERTY(REPLICATED)
	bool canBuild;

	UPROPERTY(REPLICATED)
	bool isBuilding;

	void OpenTeamChat();
	void OpenAllChat();
};
