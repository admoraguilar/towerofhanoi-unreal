// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "WGameEventSystem.h"


/**
*
*/
UWGameEventDetail::UWGameEventDetail(const class FObjectInitializer& ObjectInitializer) {

}


/**
*
*/
TMap<EGameEventName, FGameEventMulticastDelegate> UWGameEventSystem::EnumDelegates;
TMap<FString, FGameEventMulticastDelegate> UWGameEventSystem::StringDelegates;
TMap<FString, FDelegateHandle> UWGameEventSystem::DelegateHandles;


FDelegateHandle* UWGameEventSystem::GetDelegateHandle(FString Name) {
	FDelegateHandle* H = NULL;
	
	if(DelegateHandles.Contains(Name)) {
		H = &DelegateHandles[Name];
	}

	return H;
}

void UWGameEventSystem::SetDelegateHandle(FString Name, FDelegateHandle Handle) {
	if(!DelegateHandles.Contains(Name)) {
		DelegateHandles.Add(Name);
	}

	DelegateHandles[Name] = Handle;
}


void UWGameEventSystem::AddListenerEnum(EGameEventName EventName, FGameEventDelegate GameEvent) {
	UWGameEventSystem::AddListenerEnum<UObject>(EventName, GameEvent.GetUObject(), GameEvent.GetFunctionName(), nullptr);
}


void UWGameEventSystem::RemoveListenerEnum(EGameEventName EventName, FGameEventDelegate GameEvent) {
	UWGameEventSystem::RemoveListenerEnum<UObject>(EventName, GameEvent.GetUObject(), GameEvent.GetFunctionName(), nullptr);
}


void UWGameEventSystem::RaiseEventEnum(EGameEventName EventName, UWGameEventDetail* GameEventDetails) {
	UWGameEventSystem::RaiseEventEnum<UWGameEventDetail>(EventName, !GameEventDetails ? NewObject<UWGameEventDetail>(UWGameEventDetail::StaticClass()) : GameEventDetails);
}


void UWGameEventSystem::AddListenerString(FString EventName, FGameEventDelegate GameEvent) {
	UWGameEventSystem::AddListenerString<UObject>(EventName, GameEvent.GetUObject(), GameEvent.GetFunctionName(), nullptr);
}


void UWGameEventSystem::RemoveListenerString(FString EventName, FGameEventDelegate GameEvent) {
	UWGameEventSystem::RemoveListenerString<UObject>(EventName, GameEvent.GetUObject(), GameEvent.GetFunctionName(), nullptr);
}


void UWGameEventSystem::RaiseEventString(FString EventName, UWGameEventDetail* GameEventDetails) {
	UWGameEventSystem::RaiseEventString<UWGameEventDetail>(EventName, !GameEventDetails ? NewObject<UWGameEventDetail>(UWGameEventDetail::StaticClass()) : GameEventDetails);
}

