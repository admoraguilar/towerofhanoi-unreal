// Copyright Water 2017, All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "WObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_HANOI_API UWObject : public UObject {
	GENERATED_BODY()
	
public:
	virtual class UWorld* GetWorld() const;
};
