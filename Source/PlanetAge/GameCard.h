// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCard/PlanetComponent/PlanetCoefficientValues.h"
#include "GameCard.generated.h"

UCLASS()
class PLANETAGE_API AGameCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCard();

	AGameCard(const FName PlanetName, const float Kmax, const float Kmin, const float Klim, const float Vmin, const float Vmax);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	FName PlanetName;

	UPROPERTY()
	FPlanetCoefficientValues CoefficientValues;
};
