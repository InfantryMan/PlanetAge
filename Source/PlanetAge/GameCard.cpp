// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCard.h"


// Sets default values
AGameCard::AGameCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Init constructor
AGameCard::AGameCard(const FName PlanetName, 
							 const float Kmax, const float Kmin, const float Klim, 
							 const float Vmin, const float Vmax) :
							 PlanetName(PlanetName)
{
	this->CoefficientValues.Kmax = Kmax;
	this->CoefficientValues.Kmin = Kmin;
	this->CoefficientValues.Klim = Klim;
	this->CoefficientValues.Vmin = Vmin;
	this->CoefficientValues.Vmax = Vmax;
}


// Called when the game starts or when spawned
void AGameCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

