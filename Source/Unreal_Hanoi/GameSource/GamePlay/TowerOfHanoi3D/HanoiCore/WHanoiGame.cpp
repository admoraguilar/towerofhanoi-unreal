// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "WHanoiGame.h"


// Sets default values
AWHanoiGame::AWHanoiGame() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AWHanoiGame::Init() {
	// Reset values
	Time = 0.f;
	Start = false;
	GameOver = false;

	FTransform RodStart = RodStartPosition->GetTransform();
	FTransform DiskStart;
	FActorSpawnParameters RodSpawnParams;
	FActorSpawnParameters DiskSpawnParams;

	RodSpawnParams.bNoFail = true;
	DiskSpawnParams.bNoFail = true;

	// Create rods
	for(int i = 0; i < RodCount; ++i) {
		AWHanoiRod* rod = GetWorld()->SpawnActor<AWHanoiRod>(HanoiRodClass, RodStart.GetLocation(), RodStart.GetRotation().Rotator(), RodSpawnParams);
		rod->Init();
		rod->SetActorLocation(rod->GetActorLocation() + FVector(0.F, RodSpacing * i, 0.f));

		if(i == 0) FirstRod = rod;
		else if(i < RodCount) LastRod = rod;

		// Keeping track of the rod for de-initialization
		Rods.Add(rod);
	}

	// Create disks
	for(int i = DiskCount; i > 0; --i) {
		AWHanoiDisk* disk = GetWorld()->SpawnActor<AWHanoiDisk>(HanoiDiskClass, DiskStart.GetLocation(), DiskStart.GetRotation().Rotator(), DiskSpawnParams);
		disk->Init();
		//disk->SetDiskSize(FVector(disk->GetDiskSize().X + (i * DiskSizing), disk->GetDiskSize().Y + (i * DiskSizing), disk->GetDiskSize().Z));
		disk->SetDiskScale(FVector(disk->GetDiskScale().X + (i * DiskSizing), disk->GetDiskScale().Y + (i * DiskSizing), disk->GetDiskScale().Z));
		disk->SetColor(FLinearColor::MakeRandomColor());
		FirstRod->InsertDisk(disk);

		// Keeping track of the disk for de-initialization
		Disks.Add(disk);
	}
}


void AWHanoiGame::DeInit() {
	// Destroy the rods
	for(int i = 0; i < Rods.Num(); ++i) {
		Rods[i]->Destroy();
	}

	// Destroy the disks
	for(int i = 0; i < Disks.Num(); ++i) {
		Disks[i]->Destroy();
	}

	// Clear the arrays
	Rods.Empty();
	Disks.Empty();

	// Stop the game
	SetGameStart(false);
}


AWHanoiRod* AWHanoiGame::GetGoalRod() {
	return LastRod;
}


float AWHanoiGame::GetRemainingTime() {
	return TimeLimit - Time;
}


void AWHanoiGame::SetGameStart(bool value) {
	Start = value;
}


void AWHanoiGame::SetGameSettings(float timeLimit, int32 rodCount, int diskCount) {
	TimeLimit = timeLimit;
	RodCount = rodCount;
	DiskCount = diskCount;
}


void AWHanoiGame::BeginPlay() {
	Super::BeginPlay();
	
	if(InitOnStart) Init();
}


void AWHanoiGame::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(!Start || GameOver) return;

	// Timer
	Time += DeltaTime;

	// Win check
	if(LastRod) {
		if(LastRod->GetDiskCount() >= DiskCount) {
			OnWinSequence->SequenceStart();
			GameOver = true;
		}
	}

	// Time's up
	if(Time >= TimeLimit) {
		OnLoseSequence->SequenceStart();
		GameOver = true;
	}
}

