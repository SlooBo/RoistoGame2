// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UILogicBase.h"
#include "Online.h"
#include "Engine/GameInstance.h"
#include "ServerBrowserLogic.generated.h"

/**
 * 
 */
UCLASS()
class ROISTOGAME2_API UServerBrowserLogic : public UUILogicBase
{
	GENERATED_BODY()
	
public:
	UServerBrowserLogic();
	~UServerBrowserLogic();
	UFUNCTION()
	void SetUp(UUserWidget* widget, UWorld* world);
	UFUNCTION()
	void CreateSession();
	UFUNCTION()
	void FindSessions();
	UFUNCTION()
	void JoinSession(int32 searchIndex);
	UFUNCTION()
	void AddSessionToGUI(int32 searchIndex);
private:
	UPROPERTY()
	bool searchingSessions;
	
};

UCLASS()
class UServerInfo : public UObject
{
	GENERATED_BODY()

public:

	int32 searchIndex;
	UServerBrowserLogic *serverbrowser;
	UServerInfo()
	{
	}
	UFUNCTION()
		void OnClicked()
	{
		serverbrowser->JoinSession(searchIndex);
	}
};