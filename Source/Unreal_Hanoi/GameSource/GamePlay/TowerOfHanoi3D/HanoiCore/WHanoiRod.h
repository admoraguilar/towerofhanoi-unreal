// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "WEngine/WActor.h"
#include "GameSource/GamePlay/TowerOfHanoi3D/HanoiCore/WHanoiDisk.h"
#include "WHanoiRod.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_HANOI_API AWHanoiRod : public AWActor {
	GENERATED_BODY()

public:
	AWHanoiRod();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") float DiskPositionZOffset;

	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void Init();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") int32 GetDiskCount();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") AWHanoiDisk* GetTopDisk();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void InsertDisk(AWHanoiDisk* disk);
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") AWHanoiDisk* RemoveDisk();

protected:
	
	virtual void PreBeginPlay() override;

private:
	TArray<AWHanoiDisk*> Disks;
	UStaticMeshComponent* StaticMesh;
	FVector PoleMin;
};
