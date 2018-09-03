// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "WEngine/WActor.h"
#include "WEngine/Statics/WGameEventSystem.h"
#include "GameSource/GamePlay/TowerOfHanoi3D/HanoiCore/WHanoiRod.h"
#include "GameSource/GamePlay/TowerOfHanoi3D/HanoiCore/WHanoiDisk.h"
#include "WHanoiController.generated.h"

UENUM(BlueprintType)
enum class EHanoiState : uint8 {
	Idle,
	Grab, 
	Put,
};


UCLASS()
class UNREAL_HANOI_API UWHED_OnInteract_Rod : public UWGameEventDetail {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AWHanoiRod* Rod;
};


/**
 * 
 */
UCLASS()
class UNREAL_HANOI_API AWHanoiController : public AWActor {
	GENERATED_BODY()
	
public:
	AWHanoiController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiController|Properties") USoundBase* NoDiskSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiController|Properties") USoundBase* LargerDiskSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiController|Properties") USoundBase* DiskPutSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiController|Properties") USoundBase* DiskGetSound;

	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void Init();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void DeInit();

protected:
	virtual void PreBeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION() void OnInteract_Rod(UWHED_OnInteract_Rod* details);

	AWHanoiDisk* HeldDisk;
	EHanoiState State;
};
