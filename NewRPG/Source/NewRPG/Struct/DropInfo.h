#pragma once

#include "DropInfo.generated.h"


USTRUCT(BlueprintType)
struct FDropInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ItemName;		// 고유 아이템명

	UPROPERTY(EditAnywhere)
	int32 Min_Count;	// 드랍 최소개수

	UPROPERTY(EditAnywhere)
	int32 Max_Count;	// 드랍 최대개수
};