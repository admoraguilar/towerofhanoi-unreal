// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "WEngine/WObject.h"
#include "WEngine/Statics/WDebugStatics.h"
#include "WGameEventSystem.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FGameEventDelegate, UWGameEventDetail*, GameEventDetails);
DECLARE_MULTICAST_DELEGATE_OneParam(FGameEventMulticastDelegate, UWGameEventDetail*);


UENUM(BlueprintType)
enum class EGameEventName : uint8 {
	Default,
	Game_EnableInput,
	Game_DisableInput,
	GameInit_Hanoi,
	Interact_Rod,
};


/**
*
*/
UCLASS(Blueprintable)
class UNREAL_HANOI_API UWGameEventDetail : public UWObject {
	GENERATED_BODY()

protected:
	UWGameEventDetail(const class FObjectInitializer& ObjectInitializer);
};


/**
*
*/
UCLASS()
class UNREAL_HANOI_API UWGameEventSystem : public UWObject {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="WEventSystem|Methods") static void AddListenerEnum(EGameEventName EventName, FGameEventDelegate GameEvent);
	UFUNCTION(BlueprintCallable, Category="WEventSystem|Methods") static void RemoveListenerEnum(EGameEventName EventName, FGameEventDelegate GameEvent);
	UFUNCTION(BlueprintCallable, Category="WEventSystem|Methods", meta=(AdvancedDisplay = "1")) static void RaiseEventEnum(EGameEventName EventName, UWGameEventDetail* GameEventDetails = nullptr);
	UFUNCTION(BlueprintCallable, Category="WEventSystem|Methods") static void AddListenerString(FString EventName, FGameEventDelegate GameEvent);
	UFUNCTION(BlueprintCallable, Category="WEventSystem|Methods") static void RemoveListenerString(FString EventName, FGameEventDelegate GameEvent);
	UFUNCTION(BlueprintCallable, Category="WEventSystem|Methods", meta=(AdvancedDisplay = "1")) static void RaiseEventString(FString EventName, UWGameEventDetail* GameEventDetails = nullptr);

	static FDelegateHandle* GetDelegateHandle(FString Name);
	static void SetDelegateHandle(FString Name, FDelegateHandle Handle);

	template<class T> static void AddListenerEnum(EGameEventName EventName, T* UserObject, FName FunctionName, void (T::* FunctionPtr)(UWGameEventDetail*)) {
		FGameEventMulticastDelegate* D = NULL;

		if(EnumDelegates.Contains(EventName)) {
			D = &EnumDelegates[EventName];
		} else {
			EnumDelegates.Add(EventName);
			D = &EnumDelegates[EventName];
		}

		//D->__Internal_AddDynamic(UserObject, FunctionPtr, FunctionName);
		SetDelegateHandle("Enum_" + UWDebugStatics::GetEnumAsString("EGameEventName", EventName), D->AddUFunction(UserObject, FunctionName));
	}
	template<class T> static void RemoveListenerEnum(EGameEventName EventName, T* UserObject, FName FunctionName, void (T::* FunctionPtr)(UWGameEventDetail*)) {
		FGameEventMulticastDelegate* D = NULL;

		if(EnumDelegates.Contains(EventName)) {
			D = &EnumDelegates[EventName];
		} else {
			//QUICK_ON_SCREEN_DEBUG_MESSAGE_WITH_PARAMS("[Event to remove is non-existent] = %s", *UWDebugStatics::GetEnumAsString<EGameEventName>("EGameEventName", EventName));
			return;
		}

		//D->__Internal_RemoveDynamic(UserObject, FunctionPtr, FunctionName);
		//D->RemoveUFunction(UserObject, FunctionName);
		D->Remove(*GetDelegateHandle("Enum_" + UWDebugStatics::GetEnumAsString("EGameEventName", EventName)));
	}
	template<class T> static void RaiseEventEnum(EGameEventName EventName, T* GameEventDetails) {
		//QUICK_ON_SCREEN_DEBUG_MESSAGE_WITH_PARAMS("[Raising event] = %s", *UWDebugStatics::GetEnumAsString<EGameEventName>("EGameEventName", EventName));

		if(EnumDelegates.Contains(EventName)) {
			EnumDelegates[EventName].Broadcast(GameEventDetails);
		} else {
			//QUICK_ON_SCREEN_DEBUG_MESSAGE_WITH_PARAMS("[Raised event is non existent] = %s", *UWDebugStatics::GetEnumAsString<EGameEventName>("EGameEventName", EventName));
		}
	}
	template<class T> static void AddListenerString(FString EventName, T* UserObject, FName FunctionName, void (T::* FunctionPtr)(UWGameEventDetail*)) {
		FGameEventMulticastDelegate* D = NULL;

		if(StringDelegates.Contains(EventName)) {
			D = &StringDelegates[EventName];
		} else {
			StringDelegates.Add(EventName);
			D = &StringDelegates[EventName];
		}

		//D->__Internal_AddDynamic(UserObject, FunctionPtr, FunctionName);
		SetDelegateHandle("String_" + EventName, D->AddUFunction(UserObject, FunctionName));
	}
	template<class T> static void RemoveListenerString(FString EventName, T* UserObject, FName FunctionName, void (T::* FunctionPtr)(UWGameEventDetail*)) {
		FGameEventMulticastDelegate* D = NULL;

		if(StringDelegates.Contains(EventName)) {
			D = &StringDelegates[EventName];
		} else {
			//QUICK_ON_SCREEN_DEBUG_MESSAGE_WITH_PARAMS("[Event to remove is non-existent] = %s", *EventName);
			return;
		}

		//D->__Internal_RemoveDynamic(UserObject, FunctionPtr, FunctionName);
		//D->RemoveUFunction(UserObject, FunctionName);
		D->Remove(*GetDelegateHandle("String_" + EventName));
	}
	template<class T> static void RaiseEventString(FString EventName, T* GameEventDetails) {
		//QUICK_ON_SCREEN_DEBUG_MESSAGE_WITH_PARAMS("[Raising event] = %s", *EventName);

		if(StringDelegates.Contains(EventName)) {
			StringDelegates[EventName].Broadcast(GameEventDetails);
		} else {
			//QUICK_ON_SCREEN_DEBUG_MESSAGE_WITH_PARAMS("[Raised event is non existent] = %s", *EventName);
		}
	}

private:
	static TMap<EGameEventName, FGameEventMulticastDelegate> EnumDelegates;
	static TMap<FString, FGameEventMulticastDelegate> StringDelegates;
	static TMap<FString, FDelegateHandle> DelegateHandles;
};
