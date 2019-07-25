// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCardView.h"

double f(double const& v) 
{
	return v * v;
}

double f1(double const& v) 
{
	return 5 / (v + 5);
}

double f2(double const &v)
{
	return 0.5*(pow(2.71, v) + pow(2.71, -v));
}

double f3(double const &v)
{
	return sin(v);
}

void AGameCardView::OnTimerEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Up");
	this->ChartPrimitiveComponent->DrawBisChart();
}

// Because of X and Y axes in UE are right-handed, we need left-handed
void AGameCardView::AddVertex(TArray<FVector> & Vertices, FVector const& Vect) 
{
	Vertices.Add(FVector(Vect.Y, Vect.X, Vect.Z));
}

// Sets default values
AGameCardView::AGameCardView():
	ChartPosition(DEFAULT_CHART_POSITION)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}

	this->CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card mesh"));

	// Set GameCardShape
	const ConstructorHelpers::FObjectFinder<UStaticMesh> CardMeshObj(TEXT("/Game/MyContent/Shapes/Kompas/GameCard"));
	
	if (CardMeshObj.Succeeded())
	{
		this->CardMesh->SetupAttachment(RootComponent);
		this->CardMesh->SetStaticMesh(CardMeshObj.Object);
		this->CardMesh->SetMobility(EComponentMobility::Movable);
	}

	const ConstructorHelpers::FObjectFinder<UMaterial> FoundCardLeftMaterial(TEXT("/Game/MyContent/Materials/M_GameCardLeft1"));
	if (FoundCardLeftMaterial.Succeeded())
	{
		CardMesh->SetMaterial(0, FoundCardLeftMaterial.Object);
	}

	const ConstructorHelpers::FObjectFinder<UMaterial> FoundCardRightMaterial(TEXT("/Game/MyContent/Materials/M_GameCardRight"));
	if (FoundCardRightMaterial.Succeeded())
	{
		CardMesh->SetMaterial(1, FoundCardRightMaterial.Object);
	}

	this->ChartPrimitiveComponent = CreateDefaultSubobject<UChartPrimitiveComponent>(TEXT("ChartPrimitiveComponent"));
	this->ChartPrimitiveComponent->SetupAttachment(RootComponent);
	this->ChartPrimitiveComponent->SetRelativeLocation(ChartPosition);
	this->ChartPrimitiveComponent->SetupGeometry();

	this->ChartPrimitiveComponent->DrawBisChart();
}

// Called when the game starts or when spawned
void AGameCardView::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameCardView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
