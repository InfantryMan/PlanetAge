// Fill out your copyright notice in the Description page of Project Settings.


#include "ChartActor.h"

// Sets default values
AChartActor::AChartActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->ChartPrimitiveComponent = CreateDefaultSubobject<UChartPrimitiveComponent>(TEXT("ChartPrimitiveComponent"));
	this->ChartPrimitiveComponent->SetupAttachment(RootComponent);
	this->ChartPrimitiveComponent->SetupGeometry();
	TArray<FVector2D> points;

	double left = -4;
	double right = 4;
	int pointsNumber = 50;
	double step = (right - left) / (pointsNumber - 1);

	for (int i = 0; i < pointsNumber; i++)
	{
		double x = left + step * i;
		double y = 9;

		points.Add(FVector2D(x, y));
	}


	// this->ChartPrimitiveComponent->DrawBisChart(points);

}

// Called when the game starts or when spawned
void AChartActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChartActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

