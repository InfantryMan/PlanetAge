#pragma once

#include "CoreMinimal.h"
#include <Materials/Material.h>
#include "PlanetStruct.generated.h"

USTRUCT(BlueprintType) 
struct FPlanetStruct 
{ 
GENERATED_USTRUCT_BODY()

UPROPERTY(BlueprintReadWrite, Category = "GameCard|PlanetComponent")
UMaterial* Material;

UPROPERTY(BlueprintReadWrite, Category = "GameCard|PlanetComponent")
FColor Color;

UPROPERTY(BlueprintReadWrite, Category = "GameCard|PlanetComponent") 
float planetScale; 
};