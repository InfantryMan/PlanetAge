#pragma once

#include "CoreMinimal.h"
#include "PlanetCoefficientValues.generated.h"

USTRUCT(BlueprintType) 
struct FPlanetCoefficientValues
{ 
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Kmax;

	UPROPERTY(EditAnywhere)
	float Kmin;

	UPROPERTY(EditAnywhere)
	float Klim;

	UPROPERTY(EditAnywhere)
	float Vmin;

	UPROPERTY(EditAnywhere)
	float Vmax;

};