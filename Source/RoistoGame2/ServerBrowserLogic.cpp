// Fill out your copyright notice in the Description page of Project Settings.

#include "RoistoGame2.h"
#include "ServerBrowserLogic.h"
#include "NetworkSession.h"

UServerBrowserLogic::UServerBrowserLogic() :Super()
{
	/*OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UServerBrowserLogic::OnFindSessionsComplete);
	searchingSessions = false;*/
}

UServerBrowserLogic::~UServerBrowserLogic()
{
}

void UServerBrowserLogic::SetUp(UUserWidget* widget, UWorld* world)
{
	this->baseWidget = widget;
	//this->world = world;

}

void UServerBrowserLogic::CreateSession()
{

}

void UServerBrowserLogic::FindSessions()
{

}

void UServerBrowserLogic::JoinSession(int32 searchIndex)
{

}

void UServerBrowserLogic::AddSessionToGUI(int32 searchIndex)
{

}