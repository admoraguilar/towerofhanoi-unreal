// Copyright Water 2017, All Rights Reserved.

#include "Unreal_Hanoi.h"
#include "Engine.h"
#include "WEngine/Statics/WDebugStatics.h"
#include "WHanoiDisk.h"


// Sets default values
AWHanoiDisk::AWHanoiDisk() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


void AWHanoiDisk::Init() {
	// Set scale
	SetDiskScale(GetActorScale3D());
}


FVector AWHanoiDisk::GetDiskSize() {
	return DiskSize;
}


FVector AWHanoiDisk::GetDiskScale() {
	return DiskScale;
}


void AWHanoiDisk::SetDiskScale(FVector diskScale) {
	FVector min, max;
	StaticMesh->GetLocalBounds(min, max);
	DiskSize = (min + max) * diskScale;
	DiskScale = diskScale;
	SetActorScale3D(diskScale);
}


void AWHanoiDisk::SetColor(FLinearColor color) {
	DynamicMaterial->SetVectorParameterValue("Color", color);
}


void AWHanoiDisk::PreBeginPlay() {
	Super::PreBeginPlay();

	// Set references
	for(int i = 0; i < BlueprintCreatedComponents.Num(); ++i) {
		UActorComponent* Component = BlueprintCreatedComponents[i];
		if(Component->GetClass() == UStaticMeshComponent::StaticClass()) {
			StaticMesh = (UStaticMeshComponent*)Component;
		}
	}

	DynamicMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, StaticMesh->GetMaterial(0));
}