// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "WEngine/WActor.h"
#include "WEngine/WSequence.h"
#include "WEngine/Statics/WGameEventSystem.h"
#include "WEngine/Statics/WDebugStatics.h"
#include "GameSource/GamePlay/TowerOfHanoi3D/HanoiCore/WHanoiRod.h"
#include "GameSource/GamePlay/TowerOfHanoi3D/HanoiCore/WHanoiDisk.h"
#include "WHanoiGame.generated.h"


UCLASS()
class UNREAL_HANOI_API UWHED_OnGameInit_Hanoi : public UWGameEventDetail {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float TimeLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int RodCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int DiskCount;
};

/**
*
*/
UCLASS()
class UNREAL_HANOI_API AWHanoiGame : public AWActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWHanoiGame();

	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void Init();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void DeInit();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") AWHanoiRod* GetGoalRod();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") float GetRemainingTime();
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void SetGameStart(bool value);
	UFUNCTION(BlueprintCallable, Category="WHanoiRod|Methods") void SetGameSettings(float timeLimit, int32 rodCount, int diskCount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FColor> DiskColors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Blueprints") TSubclassOf<AWHanoiRod> HanoiRodClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Blueprints") TSubclassOf<AWHanoiDisk> HanoiDiskClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|References") AWSequence* OnWinSequence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|References") AWSequence* OnLoseSequence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") bool InitOnStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") AActor* RodStartPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") float TimeLimit = 120.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") float RodSpacing = .15f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") float DiskSizing = .15f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") int32 RodCount = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WHanoiGame|Settings") int32 DiskCount = 3;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AWHanoiRod*> Rods;
	TArray<AWHanoiDisk*> Disks;
	AWHanoiRod* FirstRod;
	AWHanoiRod* LastRod;
	float Time;
	bool Start;
	bool GameOver;
};
