#pragma once

#include "DropInfo.generated.h"


USTRUCT(BlueprintType)
struct FDropInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ItemName;		// ���� �����۸�

	UPROPERTY(EditAnywhere)
	int32 Min_Count;	// ��� �ּҰ���

	UPROPERTY(EditAnywhere)
	int32 Max_Count;	// ��� �ִ밳��
};