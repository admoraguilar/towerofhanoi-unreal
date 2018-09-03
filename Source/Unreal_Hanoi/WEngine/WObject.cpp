// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "WObject.h"


UWorld* UWObject::GetWorld() const {
	UObject* Outer = GetOuter();
	UWorld* World = nullptr;

	if(Outer->IsA(AActor::StaticClass())) {
		World = Outer->GetWorld();
	}

	return World;
}

