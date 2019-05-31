// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCardView.h"

double f(double const& v) {
	return v * v;
}

double f1(double const& v) {
	return 5 / (v + 5);
}

// Because of X and Y axes in UE are right-handed, we need left-handed
void addVertex(TArray<FVector> & vertices, FVector const& vect) {
	vertices.Add(FVector(vect.Y, vect.X, vect.Z));
}


// Sets default values
AGameCardView::AGameCardView()
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

	const ConstructorHelpers::FObjectFinder<UMaterial> FoundCardMaterial(TEXT("/Game/MyContent/Materials/CardMaterial"));
	
	if (FoundCardMaterial.Succeeded())
	{
		CardMesh->SetMaterial(0, FoundCardMaterial.Object);
	}

	this->ChartAxesProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ChartAxesProceduralMesh"));
	this->ChartProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ChartProceduralMesh"));

	this->ChartAxesSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChartAxesSceneComponent"));
	this->ChartAxesSceneComponent->AttachTo(RootComponent);
	this->ChartAxesSceneComponent->SetRelativeLocation(FVector(-290, 17.5, 22));
	this->ChartAxesProceduralMesh->SetupAttachment(ChartAxesSceneComponent);

	this->ChartSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChartSceneComponent"));
	this->ChartSceneComponent->AttachTo(RootComponent);
	this->ChartSceneComponent->SetRelativeLocation(FVector(-290 + thicknessOfChart, 17.5 + thicknessOfChart, 22));
	this->ChartProceduralMesh->SetupAttachment(ChartSceneComponent);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TArray<FVector> vertices;
	// axis Y
	addVertex(vertices, FVector(0, 0, 0));
	addVertex(vertices, FVector(0, lengthOfAxisY, 0));
	addVertex(vertices, FVector(thicknessOfAxes, lengthOfAxisY, 0));
	addVertex(vertices, FVector(thicknessOfAxes, 0, 0));

	// axis X
	addVertex(vertices, FVector(0, 0, 0));
	addVertex(vertices, FVector(lengthOfAxisX, 0, 0));
	addVertex(vertices, FVector(lengthOfAxisX, thicknessOfAxes, 0));
	addVertex(vertices, FVector(0, thicknessOfAxes, 0));

	// arrows on the axis Y
	int32 yAxisArrow_Mid = lengthOfAxisY - 0.16 * lengthOfArrow;
	int32 yAxisArrow_Top = lengthOfAxisY + 0.5 * lengthOfArrow;
	int32 yAxisArrow_Bottom = lengthOfAxisY - 0.5 * lengthOfArrow;
	int32 yAxisArrow_Left = thicknessOfAxes / 2 - widthOfArrow / 2;
	int32 yAxisArrow_Right = thicknessOfAxes / 2 + widthOfArrow / 2;

	addVertex(vertices, FVector(thicknessOfAxes / 2, yAxisArrow_Mid, 0));
	addVertex(vertices, FVector(thicknessOfAxes / 2, yAxisArrow_Top, 0));
	addVertex(vertices, FVector(yAxisArrow_Left, yAxisArrow_Bottom, 0));

	addVertex(vertices, FVector(thicknessOfAxes / 2, yAxisArrow_Mid, 0));
	addVertex(vertices, FVector(thicknessOfAxes / 2, yAxisArrow_Top, 0));
	addVertex(vertices, FVector(yAxisArrow_Right, yAxisArrow_Bottom, 0));

	// arrows on the axis X
	int32 xAxisArrow_Mid = lengthOfAxisX - 0.16 * lengthOfArrow;
	int32 xAxisArrow_Left = lengthOfAxisX - 0.5 * lengthOfArrow;
	int32 xAxisArrow_Right = lengthOfAxisX + 0.5 * lengthOfArrow;
	int32 xAxisArrow_Top = thicknessOfAxes / 2 + widthOfArrow / 2;
	int32 xAxisArrow_Bottom = thicknessOfAxes / 2 - widthOfArrow / 2;

	addVertex(vertices, FVector(xAxisArrow_Mid, thicknessOfAxes / 2, 0));
	addVertex(vertices, FVector(xAxisArrow_Right, thicknessOfAxes / 2, 0));
	addVertex(vertices, FVector(xAxisArrow_Left, xAxisArrow_Top, 0));

	addVertex(vertices, FVector(xAxisArrow_Mid, thicknessOfAxes / 2, 0));
	addVertex(vertices, FVector(xAxisArrow_Right, thicknessOfAxes / 2, 0));
	addVertex(vertices, FVector(xAxisArrow_Left, xAxisArrow_Bottom, 0));

	TArray<int32> triangles;
	triangles.Add(0);
	triangles.Add(3);
	triangles.Add(2);
	triangles.Add(2);
	triangles.Add(1);
	triangles.Add(0);

	triangles.Add(4);
	triangles.Add(5);
	triangles.Add(6);
	triangles.Add(6);
	triangles.Add(7);
	triangles.Add(4);

	triangles.Add(8);
	triangles.Add(9);
	triangles.Add(10);

	triangles.Add(11);
	triangles.Add(13);
	triangles.Add(12);

	triangles.Add(14);
	triangles.Add(15);
	triangles.Add(16);

	triangles.Add(17);
	triangles.Add(19);
	triangles.Add(18);

	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;

	TArray<FLinearColor> vertexColors;

	ChartAxesProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, true);

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

void AGameCardView::drawChart()
{
	this->ChartProceduralMesh->ClearAllMeshSections();
	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	double xLeftBound = 0;
	double xRightBound = 10;
	uint32 numberOfPoints = 30;

	double step = (xRightBound - xLeftBound) / (numberOfPoints - 1);

	double xMax = xRightBound;
	double yMax = -1;

	TArray<double> xValues;
	TArray<double> yValues;

	for (uint32 indexOfCurrentPoint = 0; indexOfCurrentPoint < numberOfPoints; indexOfCurrentPoint++) {
		double xValue = xLeftBound + indexOfCurrentPoint * step;
		double yValue = f1(xValue);
		if (yValue > yMax) {
			yMax = yValue;
		}
		xValues.Add(xValue);
		yValues.Add(yValue);
	}

	TArray<double> xCoords;
	TArray<double> yCoords;

	for (int32 i = 0; i < xValues.Num(); i++) {
		double xCoord = xValues[i] * this->lengthOfAxisX / xMax;
		double yCoord = yValues[i] * this->lengthOfAxisY / yMax;
		xCoords.Add(xCoord);
		yCoords.Add(yCoord);
	}

	for (int32 i = 0; i < xCoords.Num() - 1; i++) {
		FVector2D pointA(xCoords[i], yCoords[i]);
		FVector2D pointB(xCoords[i+1], yCoords[i+1]);

		FVector2D vectorAB = pointB - pointA;
		FVector2D vectorAB_normalized = vectorAB.GetSafeNormal();
		FVector2D leftHandPerpendicular_vectorAB = thicknessOfChart * FVector2D(vectorAB_normalized.Y, -vectorAB_normalized.X) + pointA;
		FVector2D rightHandPerpendicular_vectorAB = thicknessOfChart * FVector2D(-vectorAB_normalized.Y, vectorAB_normalized.X) + pointA;

		FVector2D vectorBA = pointA - pointB;
		FVector2D vectorBA_normalized = vectorAB.GetSafeNormal();
		FVector2D leftHandPerpendicular_vectorBA = thicknessOfChart * FVector2D(vectorBA_normalized.Y, -vectorBA_normalized.X) + pointB;
		FVector2D rightHandPerpendicular_vectorBA = thicknessOfChart * FVector2D(-vectorBA_normalized.Y, vectorBA_normalized.X) + pointB;

		addVertex(vertices, FVector(leftHandPerpendicular_vectorAB.X, leftHandPerpendicular_vectorAB.Y, 0));
		addVertex(vertices, FVector(leftHandPerpendicular_vectorBA.X, leftHandPerpendicular_vectorBA.Y, 0));
		addVertex(vertices, FVector(rightHandPerpendicular_vectorBA.X, rightHandPerpendicular_vectorBA.Y, 0));
		addVertex(vertices, FVector(rightHandPerpendicular_vectorAB.X, rightHandPerpendicular_vectorAB.Y, 0));

		triangles.Add(i * 4);
		triangles.Add(i * 4 + 1);
		triangles.Add(i * 4 + 2);

		triangles.Add(i * 4 + 2);
		triangles.Add(i * 4 + 3);
		triangles.Add(i * 4);
	}

	ChartProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, true);
}

