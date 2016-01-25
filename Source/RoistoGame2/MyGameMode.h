// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

UENUM(BlueprintType)
enum class InGameState : uint8
{
	Starting,
	Running,
	End,
};

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMyGameMode(const class FObjectInitializer& objectInitializer);

	//static FString GetInGameStateAsString(InGameState state);
	InGameState GetInGameState() { return inGameState; };
	//
	////Event when match has started
	//UFUNCTION(BlueprintNativeEvent, Meta = (DisplayName = "On Match Start"), Category = "Gameplay")
	//void OnMatchStart();
	//virtual void OnMatchStart_Implementation();

protected:

	//Current state of the game mode
	UPROPERTY(BluePrintReadOnly, Category = Enum)
	InGameState inGameState;

	// Time to wait before game mode starts
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Start Delay Time", ClampMin = "0"), Category = "Gameplay|Level")
	int32 startTime;
};
