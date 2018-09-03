// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "WSequence.h"


AWSequence::AWSequence() {

}


void AWSequence::SequenceStart_Implementation() {

}


void AWSequence::BeginPlay() {
	Super::BeginPlay();

	if(RunOnStart) SequenceStart();
}