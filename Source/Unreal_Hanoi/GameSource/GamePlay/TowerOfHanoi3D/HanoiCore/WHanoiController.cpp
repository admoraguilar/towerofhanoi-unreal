// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "WHanoiController.h"


// Sets default values
AWHanoiController::AWHanoiController() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


void AWHanoiController::Init() {
	State = EHanoiState::Grab;
}


void AWHanoiController::DeInit() {
	State = EHanoiState::Idle;
}


void AWHanoiController::PreBeginPlay() {
	UWGameEventSystem::AddListenerEnum<AWHanoiController>(EGameEventName::Interact_Rod, this, FName("OnInteract_Rod"), nullptr);
}


void AWHanoiController::EndPlay(EEndPlayReason::Type EndPlayReason) {
	UWGameEventSystem::RemoveListenerEnum<AWHanoiController>(EGameEventName::Interact_Rod, this, FName("OnInteract_Rod"), nullptr);
}


void AWHanoiController::OnInteract_Rod(UWHED_OnInteract_Rod* details) {
	//QUICK_ON_SCREEN_DEBUG_MESSAGE("Event received");

	switch(State) {
		case EHanoiState::Grab:
			if(details->Rod->GetDiskCount() <= 0) {
				QUICK_ON_SCREEN_DEBUG_MESSAGE("The rod has no disk.");
				UGameplayStatics::PlaySound2D(this, NoDiskSound);
				return;
			}
			HeldDisk = details->Rod->RemoveDisk();
			UGameplayStatics::PlaySound2D(this, DiskGetSound);
			State = EHanoiState::Put;
			break;
		case EHanoiState::Put:
			AWHanoiDisk* d = details->Rod->GetTopDisk();
			if(d) {
				if(HeldDisk->GetDiskScale().X > d->GetDiskScale().X) {
					QUICK_ON_SCREEN_DEBUG_MESSAGE("Held disk is larger than the rod's top disk.");
					UGameplayStatics::PlaySound2D(this, LargerDiskSound);
					return;
				}
			}
			details->Rod->InsertDisk(HeldDisk);
			UGameplayStatics::PlaySound2D(this, DiskPutSound);
			HeldDisk = NULL;
			State = EHanoiState::Grab;
			break;
	}
}