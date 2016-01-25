// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

UENUM(BlueprintType)
enum class Menutype : uint8
{
	MAIN_MENU		UMETA(DisplayName = "MAIN_MENU"),
	GAME_UI			UMETA(DisplayName = "GAME_UI"),
	SERVER_BROWSER	UMETA(DisplayName = "SERVER_BROWSER"),
	SCOREBOARD		UMETA(DisplayName = "SCOREBOARD"),
	NO_UI			UMETA(DisplayName = "NO_UI")
};

USTRUCT()
struct FScreenMessage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float currentTime;
	UPROPERTY()
		float maxTime;
	/*UPROPERTY()
		UUserWidget *widget;*/

	//Constructor
	/*FScreenMessage()
	{
		currentTime = 0.0f;
		this->widget = nullptr;
	}*/
};

//
///**
// * 
// */
//UCLASS()
//class ROISTOGAME2_API APlayerHUD : public AHUD
//{
//	GENERATED_BODY()
//	
//public:
//	//Sets defaul values for this actor's propertie
//	APlayerHUD(const FObjectInitializer& PCIP);
//	
//	UFUNCTION(BlueprintCallable, Category = "UI")
//		void BeginPlayCpluplus();
//	//virtual void BeginPlay() override;
//
//	//Called every frame
//	virtual void Tick(float DeltaSeconds) override;
////	UFUNCTION()
////		void DrawHUD() override;
////	UFUNCTION(BlueprintCallable, Category = "UI")
////	void changeUIElement(MenuType menu);
////	MenuType GetCurrentUI();
////	UFUNCTION(Exec)
////	void ChangeUI(int32 interfaceID);
////	
////	/*UFUNCTION()
////	UUILogicBase *GetCurrentUILogic();*/
////	UFUNCTION(Exec)
////	void CreateTestHavoc();
////	UFUNCTION(Exec)
////	void ShowText(FString text, int32 fontsize = 32, float anchorX = 0.5f, float anchorY = 0.5f, int32 lifetime = 2, FLinearColor color = FLinearColor::White);
////private:
////
////	UPROPERTY()
////	TArray<FScreenMessage> screenMessages;
////	UPROPERTY()
////	MenuType currentMenu;
////	UPROPERTY()
////	/*TArray<UUserWidget*> widgets;
////	UUserWidget* chageUIElement(UClass* uitype);*/
////
////	//UPROPERTY()
////	//UClass* emoteWindowClass;
////	//UPROPERTY()
////	//UClass *mainMenuClass;
////	//UPROPERTY()
////	//UClass *gameUIClass;
////	//UPROPERTY()
////	//UClass *serverBrowserClass;
////	//UPROPERTY()
////	//UClass *turretClass;
////	/*UPROPERTY()
////	TArray<UUILogicBase*> logicClasses;*/
////	/*void ClearAllWidgets();
////	UUserWidget* widgetInstance;*/
//};
