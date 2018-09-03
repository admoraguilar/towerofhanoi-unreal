// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "WActor.generated.h"

UCLASS()
class UNREAL_HANOI_API AWActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWActor();

protected:
	virtual void PostInitializeComponents() override;
	virtual void PreBeginPlay();

	UFUNCTION(BlueprintNativeEvent, Category = "WActor|Methods") void ExecPreBeginPlay();
	virtual void ExecPreBeginPlay_Implementation();
};
