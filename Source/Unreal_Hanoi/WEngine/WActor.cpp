// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "WActor.h"


// Sets default values
AWActor::AWActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


void AWActor::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if(GetWorld()->WorldType != EWorldType::Editor && GetWorld()->WorldType != EWorldType::EditorPreview) {
		ExecPreBeginPlay();
		PreBeginPlay();
	}
}


void AWActor::PreBeginPlay() {

}


void AWActor::ExecPreBeginPlay_Implementation() {

}


