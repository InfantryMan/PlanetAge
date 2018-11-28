#pragma once

#include "CoreMinimal.h"
#include "PositionSettings.generated.h"

USTRUCT(BlueprintType) 
struct FPositionSettings
{ 
GENERATED_BODY()

UPROPERTY(BlueprintReadWrite, Category = "Positioning")
int32 BeginX;

UPROPERTY(BlueprintReadWrite, Category = "Positioning")
int32 BeginY;

UPROPERTY(BlueprintReadWrite, Category = "Positioning") 
int32 CoefX;

UPROPERTY(BlueprintReadWrite, Category = "Positioning") 
int32 CoefY;
};