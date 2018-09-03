// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "WEngine/WActor.h"
#include "WHanoiDisk.generated.h"

UCLASS()
class UNREAL_HANOI_API AWHanoiDisk : public AWActor {
	GENERATED_BODY()

public:
	AWHanoiDisk();

	UFUNCTION(BlueprintCallable, Category="WHanoiDisk|Methods") void Init();
	UFUNCTION(BlueprintCallable, Category="WHanoiDisk|Methods") FVector GetDiskSize();
	UFUNCTION(BlueprintCallable, Category="WHanoiDisk|Methods") FVector GetDiskScale();
	UFUNCTION(BlueprintCallable, Category="WHanoiDisk|Methods") void SetDiskScale(FVector diskScale);
	UFUNCTION(BlueprintCallable, Category="WHanoiDisk|Methods") void SetColor(FLinearColor color);

protected:
	virtual void PreBeginPlay() override;

private:
	UStaticMeshComponent* StaticMesh;
	UMaterialInstanceDynamic* DynamicMaterial;
	FVector DiskSize;
	FVector DiskScale;
};
