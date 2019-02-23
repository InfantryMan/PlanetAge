#pragma once

#include "CoreMinimal.h"
#include "PlanetCoefficientValues.generated.h"

USTRUCT(BlueprintType)
struct FPlanetCoefficientValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float Kmax = 0;

	UPROPERTY(EditAnywhere)
		float Kmin = 0;

	UPROPERTY(EditAnywhere)
		float Klim = 0;

	UPROPERTY(EditAnywhere)
		float Vmin = 0;

	UPROPERTY(EditAnywhere)
		float Vmax = 0;

};