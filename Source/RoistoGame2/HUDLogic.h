// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UILogicBase.h"
#include "HUDLogic.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API UHUDLogic : public UUILogicBase
{
	GENERATED_BODY()
	
public:
	UHUDLogic();
	~UHUDLogic();
	UFUNCTION()
	void SetUp(UUserWidget* widget, UWorld *world);

	void Update() override;
protected:
	UWorld *world;

	UTextBlock *raceTimeLeft;
	UTextBlock *currentRoundText;
};
