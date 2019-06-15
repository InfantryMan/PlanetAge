// Fill out your copyright notice in the Description page of Project Settings.


#include "ChartPrimitiveComponent.h"

UChartPrimitiveComponent::UChartPrimitiveComponent() :
	RectHeight(DEFAULT_RECT_HEIGHT),
	RectWidth(DEFAULT_RECT_WIDTH),
	Offset(DEFAULT_OFFSET),
	AxesThickness(DEFAULT_AXES_THICKNESS),
	ChartThickness(DEFAULT_CHART_THICKNESS),
	ArrowLength(DEFAULT_ARROW_LENGTH),
	ArrowWidth(DEFAULT_ARROW_WIDTH)
{
}

UChartPrimitiveComponent::~UChartPrimitiveComponent()
{
}

UChartPrimitiveComponent::UChartPrimitiveComponent(int32 _rectHeight, int32 _rectWidth, int32 _offset, int32 _axesThickness, int32 _chartThickness, int32 _arrowLength, int32 _arrowWidth) :
	RectHeight(_rectHeight),
	RectWidth(_rectWidth),
	Offset(_offset),
	AxesThickness(_axesThickness),
	ChartThickness(_chartThickness),
	ArrowLength(_arrowLength),
	ArrowWidth(_arrowWidth)
{
}

void UChartPrimitiveComponent::SetupGeometry()
{
	this->ChartAxesProceduralMesh = NewObject<UProceduralMeshComponent>(this, TEXT("ChartAxesProceduralMesh"));
	this->ChartProceduralMesh = NewObject<UProceduralMeshComponent>(this, TEXT("ChartProceduralMesh"));
	this->RectangleProceduralMesh = NewObject<UProceduralMeshComponent>(this, TEXT("RectangleProceduralMesh"));

	this->ChartAxesProceduralMesh->SetupAttachment((USceneComponent*)this);
	this->ChartProceduralMesh->SetupAttachment((USceneComponent*)this);
	this->RectangleProceduralMesh->SetupAttachment((USceneComponent*)this);

	DrawRectangle();
	// DrawAxes();

	// this->ChartAxesSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChartAxesSceneComponent"));
	// this->ChartAxesSceneComponent->SetRelativeLocation(FVector(-290, 17.5, 22));
	// this->ChartAxesProceduralMesh->SetupAttachment(ChartAxesSceneComponent);


	/*
	this->ChartSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChartSceneComponent"));
	this->ChartSceneComponent->SetupAttachment(ParentRootComponent);
	this->ChartSceneComponent->SetRelativeLocation(FVector(-290 + ChartThickness, 17.5 + ChartThickness, 22));

	this->ChartProceduralMesh->SetupAttachment(ChartSceneComponent);
	*/
}

void UChartPrimitiveComponent::DrawRectangle()
{
	TArray<FVector> vertices;
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(RectWidth, 0, 0));
	vertices.Add(FVector(RectWidth, -RectHeight, 0));
	vertices.Add(FVector(0, -RectHeight, 0));

	TArray<int32> triangles;
	triangles.Add(0);
	triangles.Add(1);
	triangles.Add(3);
	triangles.Add(1);
	triangles.Add(2);
	triangles.Add(3);

	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;

	TArray<FLinearColor> vertexColors;

	RectangleProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, false);
	
	TArray<FVector> vertices1;
	vertices1.Add(FVector(100, 100, 0));
	vertices1.Add(FVector(RectWidth + 100, 100, 0));
	vertices1.Add(FVector(RectWidth + 100, -RectHeight + 100, 0));
	vertices1.Add(FVector(100, -RectHeight + 100, 0));

	TArray<int32> triangles1;
	triangles1.Add(0);
	triangles1.Add(1);
	triangles1.Add(3);
	triangles1.Add(1);
	triangles1.Add(2);
	triangles1.Add(3);

	TArray<FLinearColor> vertexColors1;

	vertexColors1.Add(FLinearColor::Black);
	vertexColors1.Add(FLinearColor::Black);
	vertexColors1.Add(FLinearColor::Black);
	vertexColors1.Add(FLinearColor::Black);

	TArray<FVector> normals1;
	TArray<FVector2D> UV01;
	TArray<FProcMeshTangent> tangents1;

	RectangleProceduralMesh->CreateMeshSection_LinearColor(1, vertices1, triangles1, normals1, UV01, vertexColors1, tangents1, false);
}

void UChartPrimitiveComponent::DrawAxes()
{
	/*
	int32 XAxisLength = RectWidth - 2 * Offset;
	int32 YAxisLength = RectHeight - 2 * Offset;

	TArray<FVector> vertices;
	// axis Y
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(0, lengthOfAxisY, 0));
	vertices.Add(FVector(thicknessOfAxes, lengthOfAxisY, 0));
	vertices.Add(FVector(thicknessOfAxes, 0, 0));

	// axis X
	vertices.Add(FVector(0, 0, 0));
	vertices.Add(FVector(lengthOfAxisX, 0, 0));
	vertices.Add(FVector(lengthOfAxisX, thicknessOfAxes, 0));
	vertices.Add(FVector(0, thicknessOfAxes, 0));

	// arrows on the axis Y
	int32 yAxisArrow_Mid = lengthOfAxisY - 0.16 * lengthOfArrow;
	int32 yAxisArrow_Top = lengthOfAxisY + 0.5 * lengthOfArrow;
	int32 yAxisArrow_Bottom = lengthOfAxisY - 0.5 * lengthOfArrow;
	int32 yAxisArrow_Left = thicknessOfAxes / 2 - widthOfArrow / 2;
	int32 yAxisArrow_Right = thicknessOfAxes / 2 + widthOfArrow / 2;

	vertices.Add(FVector(thicknessOfAxes / 2, yAxisArrow_Mid, 0));
	vertices.Add(FVector(thicknessOfAxes / 2, yAxisArrow_Top, 0));
	vertices.Add(FVector(yAxisArrow_Left, yAxisArrow_Bottom, 0));

	vertices.Add(FVector(thicknessOfAxes / 2, yAxisArrow_Mid, 0));
	vertices.Add(FVector(thicknessOfAxes / 2, yAxisArrow_Top, 0));
	vertices.Add(FVector(yAxisArrow_Right, yAxisArrow_Bottom, 0));

	// arrows on the axis X
	int32 xAxisArrow_Mid = lengthOfAxisX - 0.16 * lengthOfArrow;
	int32 xAxisArrow_Left = lengthOfAxisX - 0.5 * lengthOfArrow;
	int32 xAxisArrow_Right = lengthOfAxisX + 0.5 * lengthOfArrow;
	int32 xAxisArrow_Top = thicknessOfAxes / 2 + widthOfArrow / 2;
	int32 xAxisArrow_Bottom = thicknessOfAxes / 2 - widthOfArrow / 2;

	vertices.Add(FVector(xAxisArrow_Mid, thicknessOfAxes / 2, 0));
	vertices.Add(FVector(xAxisArrow_Right, thicknessOfAxes / 2, 0));
	vertices.Add(FVector(xAxisArrow_Left, xAxisArrow_Top, 0));

	vertices.Add(FVector(xAxisArrow_Mid, thicknessOfAxes / 2, 0));
	vertices.Add(FVector(xAxisArrow_Right, thicknessOfAxes / 2, 0));
	vertices.Add(FVector(xAxisArrow_Left, xAxisArrow_Bottom, 0));

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
	*/
}