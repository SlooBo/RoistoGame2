// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define STRINGIFY(str) L#str

/**
 * 
 */
class ROISTOGAME2_API Util
{
public:
	Util();
	~Util();

	static class APlayerCarCode* GetLocalPlayer(UWorld* world);
	static class APlayerCarCode* GetPlayerCar(APlayerController* player);
	static int32 GetNumPlayers(UWorld* world);

	//from https://wiki.unrealengine.com/Dynamic_Load_Object
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) 
			return NULL;
			//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}
	static FORCEINLINE FName GetObjPath(const UObject* Obj)
	{
		if (!Obj) return NAME_None;
		if (!Obj->IsValidLowLevel()) return NAME_None;
		//~

		FStringAssetReference ThePath = FStringAssetReference(Obj);

		if (!ThePath.IsValid()) return NAME_None;

		//The Class FString Name For This Object
		FString Str = Obj->GetClass()->GetDescription();

		Str += "'";
		Str += ThePath.ToString();
		Str += "'";

		return FName(*Str);
	}

	// Distance to player's capsule component
	static float GetDistanceToPlayer(const AActor* object, const class APlayerCarCode* player);

};
