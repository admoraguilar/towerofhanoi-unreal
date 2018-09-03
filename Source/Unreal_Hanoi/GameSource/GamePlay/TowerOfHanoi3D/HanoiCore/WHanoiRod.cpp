// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "WEngine/Statics/WDebugStatics.h"
#include "WHanoiRod.h"


// Sets default values
AWHanoiRod::AWHanoiRod() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


void AWHanoiRod::Init() {
	FVector min, max;
	StaticMesh->GetLocalBounds(min, max);
	PoleMin = min;
}


int32 AWHanoiRod::GetDiskCount() {
	return Disks.Num();
}


AWHanoiDisk* AWHanoiRod::GetTopDisk() {
	return Disks.Num() != 0 ? Disks.Top() : NULL;
}


void AWHanoiRod::InsertDisk(AWHanoiDisk* disk) {
	disk->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	disk->SetActorRelativeLocation(FVector(0.f, 0.f, PoleMin.Z + DiskPositionZOffset + (disk->GetDiskSize().Z * Disks.Num())));
	Disks.Push(disk);
}


AWHanoiDisk* AWHanoiRod::RemoveDisk() {
	AWHanoiDisk* disk = Disks.Pop();
	disk->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	disk->SetActorRelativeLocation(FVector(0.f, 0.f, 5.f));
	return disk;
}


void AWHanoiRod::PreBeginPlay() {
	Super::PreBeginPlay();

	// Set references
	for(int i = 0; i < BlueprintCreatedComponents.Num(); ++i) {
		UActorComponent* Component = BlueprintCreatedComponents[i];
		if(Component->GetClass() == UStaticMeshComponent::StaticClass()) {
			StaticMesh = (UStaticMeshComponent*)Component;
		}
	}
}