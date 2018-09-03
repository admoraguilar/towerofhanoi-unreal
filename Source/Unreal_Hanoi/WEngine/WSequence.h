// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "WEngine/WActor.h"
#include "WSequence.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_HANOI_API AWSequence : public AWActor {
	GENERATED_BODY()

public:
	AWSequence();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool RunOnStart = true;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="WSequence|Methods") void SequenceStart();
	virtual void SequenceStart_Implementation();

protected:
	virtual void BeginPlay() override;
};
