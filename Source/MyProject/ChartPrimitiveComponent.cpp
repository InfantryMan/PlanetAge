// Fill out your copyright notice in the Description page of Project Settings.


#include "ChartPrimitiveComponent.h"
#include <iostream>

UChartPrimitiveComponent::UChartPrimitiveComponent() :
	RectHeight(DEFAULT_RECT_HEIGHT),
	RectWidth(DEFAULT_RECT_WIDTH),
	Offset(DEFAULT_OFFSET),
	AvailableCoef(DEFAULT_AVAILABLE_COEF),
	AxesThickness(DEFAULT_AXES_THICKNESS),
	ChartThickness(DEFAULT_CHART_THICKNESS),
	ArrowLength(DEFAULT_ARROW_LENGTH),
	ArrowWidth(DEFAULT_ARROW_WIDTH),
	TextSize(DEFAULT_TEXT_SIZE),
	TextWidth(DEFAULT_TEXT_WIDTH),
	TextColor(DEFAULT_TEXT_COLOR),
	NumberSize(DEFAULT_NUMBER_SIZE),
	NumberWidth(DEFAULT_NUMBER_WIDTH),
	NumberColor(DEFAULT_NUMBER_COLOR),
	DottedLineWidth(DEFAULT_DOTTED_LINE_WIDTH),
	DottedLineLength(DEFAULT_DOTTED_LINE_LENGTH),
	DottedLineGap(DEFAULT_DOTTED_LINE_GAP)
{
	XAxisLength = RectWidth - 2 * Offset - 0.5 * ArrowLength;
	YAxisLength = RectHeight - 2 * Offset - 0.5 * ArrowLength;

	// Xavailable = (XAxisLength - 1.1 * ArrowLength) * AvailableCoef;
	// Yavailable = (YAxisLength - 1.1 * ArrowLength) * AvailableCoef;
	
	Xavailable = XAxisLength;
	Yavailable = YAxisLength;
}

UChartPrimitiveComponent::~UChartPrimitiveComponent()
{
}

UChartPrimitiveComponent::UChartPrimitiveComponent(int32 _rectHeight, int32 _rectWidth, int32 _offset, int32 _axesThickness, int32 _chartThickness, int32 _arrowLength, int32 _arrowWidth) :
	RectHeight(_rectHeight),
	RectWidth(_rectWidth),
	Offset(_offset),
	AvailableCoef(DEFAULT_AVAILABLE_COEF),
	AxesThickness(_axesThickness),
	ChartThickness(_chartThickness),
	ArrowLength(_arrowLength),
	ArrowWidth(_arrowWidth),
	TextSize(DEFAULT_TEXT_SIZE),
	TextWidth(DEFAULT_TEXT_WIDTH),
	TextColor(DEFAULT_TEXT_COLOR),
	NumberSize(DEFAULT_NUMBER_SIZE),
	NumberWidth(DEFAULT_NUMBER_WIDTH),
	NumberColor(DEFAULT_NUMBER_COLOR),
	DottedLineWidth(DEFAULT_DOTTED_LINE_WIDTH),
	DottedLineLength(DEFAULT_DOTTED_LINE_LENGTH),
	DottedLineGap(DEFAULT_DOTTED_LINE_GAP)
{
	XAxisLength = RectWidth - 2 * Offset;
	YAxisLength = RectHeight - 2 * Offset;
}

void UChartPrimitiveComponent::SetupGeometry()
{
	this->ChartAxesProceduralMesh = NewObject<UProceduralMeshComponent>(this, TEXT("ChartAxesProceduralMesh"));
	this->ChartProceduralMesh = NewObject<UProceduralMeshComponent>(this, TEXT("ChartProceduralMesh"));
	this->RectangleProceduralMesh = NewObject<UProceduralMeshComponent>(this, TEXT("RectangleProceduralMesh"));

	this->ChartSceneComponent = NewObject<USceneComponent>(this, TEXT("ChartSceneComponent"));
	this->OriginSceneComponent = NewObject<USceneComponent>(this, TEXT("OriginSceneComponent"));

	this->RectangleProceduralMesh->SetupAttachment((USceneComponent*)this);

	this->ChartSceneComponent->SetupAttachment((USceneComponent*)this);
	this->ChartSceneComponent->SetRelativeLocation(FVector(Offset, -Offset, 1));
	this->ChartAxesProceduralMesh->SetupAttachment(this->ChartSceneComponent);

	this->OriginSceneComponent->SetupAttachment(this->ChartSceneComponent);
	this->ChartProceduralMesh->SetupAttachment(this->OriginSceneComponent);

	DrawRectangle();
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
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));
	normals.Add(FVector(1, 0, 0));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(1, 0));
	UV0.Add(FVector2D(1, 1));
	UV0.Add(FVector2D(0, 1));

	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0, 0, 0));
	vertexColors.Add(FLinearColor(100, 100, 100));
	vertexColors.Add(FLinearColor(0, 100, 0));
	vertexColors.Add(FLinearColor(0, 0, 100));

	RectangleProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, false);

	const ConstructorHelpers::FObjectFinder<UMaterial> ChartBackgroundMaterial = (TEXT("/Game/MyContent/Materials/M_ChartBackground"));
	if (ChartBackgroundMaterial.Succeeded())
	{
		RectangleProceduralMesh->SetMaterial(0, ChartBackgroundMaterial.Object);
	}
}

void UChartPrimitiveComponent::DrawOrtChart(TArray<FVector2D> Points)
{
	double Xmin = DBL_MAX, Xmax = -DBL_MAX, Ymin = DBL_MAX, Ymax = -DBL_MAX;
	for (int32 i = 0; i < Points.Num(); i++)
	{
		if (Points[i].X < Xmin) { Xmin = Points[i].X; }
		if (Points[i].X > Xmax) { Xmax = Points[i].X; }
		if (Points[i].Y < Ymin) { Ymin = Points[i].Y; }
		if (Points[i].Y > Ymax) { Ymax = Points[i].Y; }
	}

	double Xcoef = Xavailable / abs(Xmax - Xmin);
	double Ycoef = Yavailable / abs(Ymax - Ymin);

	FVector2D origin;
	double Xorigin, Yorigin;

	if (Xmin < 0)
	{
		Xorigin = (-1) * Xmin * Xcoef;
	}
	else
	{
		Xorigin = 0;
	}

	if (Ymin < 0)
	{
		Yorigin = (-1) * Ymin * Ycoef;
	}
	else
	{
		Yorigin = 0;
	}

	origin.Set(Xorigin, Yorigin);
	this->OriginSceneComponent->SetRelativeLocation(FVector(origin.X, -origin.Y, 1));

	DrawAxes(origin);

	TArray<FVector2D> EnginePoints;
	for (int i = 0; i < Points.Num(); i++)
	{
		FVector2D EnginePoint(Points[i].X * Xcoef, Points[i].Y * Ycoef);
		EnginePoints.Push(EnginePoint);
	}

	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	for (int32 i = 0; i < EnginePoints.Num() - 1; i++)
	{
		FVector2D pointA(EnginePoints[i].X, EnginePoints[i].Y);
		FVector2D pointB(EnginePoints[i + 1].X, EnginePoints[i + 1].Y);

		FVector2D vectorAB = pointB - pointA;
		FVector2D vectorAB_normalized = vectorAB.GetSafeNormal();
		FVector2D leftHandPerpendicular_vectorAB = ChartThickness / 2 * FVector2D(vectorAB_normalized.Y, -vectorAB_normalized.X) + pointA;
		FVector2D rightHandPerpendicular_vectorAB = ChartThickness / 2 * FVector2D(-vectorAB_normalized.Y, vectorAB_normalized.X) + pointA;

		FVector2D vectorBA = pointA - pointB;
		FVector2D vectorBA_normalized = vectorAB.GetSafeNormal();
		FVector2D leftHandPerpendicular_vectorBA = ChartThickness / 2 * FVector2D(vectorBA_normalized.Y, -vectorBA_normalized.X) + pointB;
		FVector2D rightHandPerpendicular_vectorBA = ChartThickness / 2 * FVector2D(-vectorBA_normalized.Y, vectorBA_normalized.X) + pointB;

		vertices.Add(FVector(leftHandPerpendicular_vectorAB.X, -leftHandPerpendicular_vectorAB.Y, 0));
		vertices.Add(FVector(leftHandPerpendicular_vectorBA.X, -leftHandPerpendicular_vectorBA.Y, 0));
		vertices.Add(FVector(rightHandPerpendicular_vectorBA.X, -rightHandPerpendicular_vectorBA.Y, 0));
		vertices.Add(FVector(rightHandPerpendicular_vectorAB.X, -rightHandPerpendicular_vectorAB.Y, 0));

		triangles.Add(i * 4);
		triangles.Add(i * 4 + 1);
		triangles.Add(i * 4 + 2);

		triangles.Add(i * 4 + 2);
		triangles.Add(i * 4 + 3);
		triangles.Add(i * 4);
	}

	ChartProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, false);
}

void UChartPrimitiveComponent::DrawBisChart()
{

	TArray<FVector2D> Points;

	Points.Add(FVector2D(-5, -4));
	Points.Add(FVector2D(-3, 2));
	Points.Add(FVector2D(-1, -3));
	Points.Add(FVector2D(4, 4));


	double Xmin = DBL_MAX, Xmax = -DBL_MAX, Ymin = DBL_MAX, Ymax = -DBL_MAX;
	for (int32 i = 0; i < Points.Num(); i++)
	{
		if (Points[i].X < Xmin) { Xmin = Points[i].X; }
		if (Points[i].X > Xmax) { Xmax = Points[i].X; }
		if (Points[i].Y < Ymin) { Ymin = Points[i].Y; }
		if (Points[i].Y > Ymax) { Ymax = Points[i].Y; }
	}

	Xavailable = (XAxisLength - 1.1 * ArrowLength) * AvailableCoef;
	Yavailable = (YAxisLength - 1.1 * ArrowLength) * AvailableCoef;

	if (Xmin > 0) { Xmin = 0;  Xavailable = XAxisLength - 1.1 * ArrowLength - TextSize; }
	if (Ymin > 0) { Ymin = 0;  Yavailable = YAxisLength - 1.1 * ArrowLength - TextSize; }
	if (Xmax < 0) { Xmax = 0;  Xavailable = XAxisLength - 1.1 * ArrowLength; }
	if (Ymax < 0) { Ymax = 0;  Yavailable = YAxisLength - 1.1 * ArrowLength; }

	double Xcoef = Xavailable / abs(Xmax - Xmin);
	double Ycoef = Yavailable / abs(Ymax - Ymin);

	// FVector2D origin(TextSize + (1 - AvailableCoef) * XAxisLength / 2 - Xavailable / 2, TextSize - ArrowLength);
	// FVector2D origin(TextSize, TextSize);
	FVector2D origin(TextSize, TextSize);
	if (Xmin < 0 && Xmin < TextSize)
	{
		origin.X = (-1) * Xmin * Xcoef;
		origin.X += (1 - AvailableCoef) * XAxisLength / 2 + ArrowLength / 3;
	}
	if (Ymin < 0 && Ymin < TextSize)
	{
		origin.Y = (-1) * Ymin * Ycoef;
		origin.Y += (1 - AvailableCoef) * YAxisLength / 2 + ArrowLength / 3;
	}

	this->OriginSceneComponent->SetRelativeLocation(FVector(origin.X, -origin.Y, 1));

	DrawAxes(origin);

	TArray<FVector2D> EnginePoints;
	for (int i = 0; i < Points.Num(); i++)
	{
		FVector2D EnginePoint(Points[i].X * Xcoef, Points[i].Y * Ycoef);
		EnginePoints.Push(EnginePoint);
	}

	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	FVector2D O1O2 = FVector2D(EnginePoints[1].X - EnginePoints[0].X, EnginePoints[1].Y - EnginePoints[0].Y);
	FVector2D O2O1 = -O1O2;
	FVector2D O2O3 = FVector2D(EnginePoints[2].X - EnginePoints[1].X, EnginePoints[2].Y - EnginePoints[1].Y);
	FVector2D O3O2 = -O2O3;
	FVector2D O1O2_normal = O1O2.GetSafeNormal();
	FVector2D topLeft, bottomLeft, topRight, bottomRight;
	topLeft = FVector2D(-O1O2_normal.Y, O1O2_normal.X) * ChartThickness / 2 + EnginePoints[0];
	bottomLeft = FVector2D(O1O2_normal.Y, -O1O2_normal.X) * ChartThickness / 2 + EnginePoints[0];

	float cos2a = FVector2D::DotProduct(O2O1, O2O3) / (O2O1.Size() * O2O3.Size());
	float sina = sqrt((1 - cos2a) / 2);
	float x = ChartThickness / 2 / sina;
	FVector2D biss = x * (O2O1.GetSafeNormal() + O2O3.GetSafeNormal()).GetSafeNormal();

	if (biss.Y > 0)
	{
		topRight = FVector2D(EnginePoints[1].X + biss.X, EnginePoints[1].Y + biss.Y);
		bottomRight = FVector2D(EnginePoints[1].X - biss.X, EnginePoints[1].Y - biss.Y);
	}
	else
	{
		topRight = FVector2D(EnginePoints[1].X - biss.X, EnginePoints[1].Y - biss.Y);
		bottomRight = FVector2D(EnginePoints[1].X + biss.X, EnginePoints[1].Y + biss.Y);
	}

	vertices.Add(FVector(bottomLeft.X, -bottomLeft.Y, 0));
	vertices.Add(FVector(topLeft.X, -topLeft.Y, 0));
	vertices.Add(FVector(topRight.X, -topRight.Y, 0));
	vertices.Add(FVector(bottomRight.X, -bottomRight.Y, 0));

	triangles.Add(0);
	triangles.Add(2);
	triangles.Add(1);
	triangles.Add(2);
	triangles.Add(0);
	triangles.Add(3);

	for (int i = 2; i < EnginePoints.Num() - 1; i++)
	{
		O1O2 = O2O3;
		O2O1 = -O1O2;
		O2O3 = FVector2D(EnginePoints[i + 1].X - EnginePoints[i].X, EnginePoints[i + 1].Y - EnginePoints[i].Y);
		O3O2 = -O2O3;
		bottomLeft = bottomRight;
		topLeft = topRight;

		cos2a = FVector2D::DotProduct(O2O1, O2O3) / (O2O1.Size() * O2O3.Size());
		sina = sqrt((1 - cos2a) / 2);
		x = ChartThickness / 2 / sina;
		biss = x * (O2O1.GetSafeNormal() + O2O3.GetSafeNormal()).GetSafeNormal();

		if (biss.Y > 0)
		{
			topRight = FVector2D(EnginePoints[i].X + biss.X, EnginePoints[i].Y + biss.Y);
			bottomRight = FVector2D(EnginePoints[i].X - biss.X, EnginePoints[i].Y - biss.Y);
		}
		else
		{
			topRight = FVector2D(EnginePoints[i].X - biss.X, EnginePoints[i].Y - biss.Y);
			bottomRight = FVector2D(EnginePoints[i].X + biss.X, EnginePoints[i].Y + biss.Y);
		}

		vertices.Add(FVector(topRight.X, -topRight.Y, 0));
		vertices.Add(FVector(bottomRight.X, -bottomRight.Y, 0));

		triangles.Add(i * 2 - 1);
		triangles.Add(i * 2);
		triangles.Add(i * 2 - 2);

		triangles.Add(i * 2);
		triangles.Add(i * 2 - 1);
		triangles.Add(i * 2 + 1);
	}

	O1O2 = O2O3;
	O2O1 = -O1O2;
	bottomLeft = bottomRight;
	topLeft = topRight;
	O1O2_normal = O1O2.GetSafeNormal();
	topRight = FVector2D(-O1O2_normal.Y, O1O2_normal.X) * ChartThickness / 2 + EnginePoints[EnginePoints.Num() - 1];
	bottomRight = FVector2D(O1O2_normal.Y, -O1O2_normal.X) * ChartThickness / 2 + EnginePoints[EnginePoints.Num() - 1];

	vertices.Add(FVector(topRight.X, -topRight.Y, 0));
	vertices.Add(FVector(bottomRight.X, -bottomRight.Y, 0));

	triangles.Add((EnginePoints.Num() - 1) * 2 - 1);
	triangles.Add((EnginePoints.Num() - 1) * 2);
	triangles.Add((EnginePoints.Num() - 1) * 2 - 2);

	triangles.Add((EnginePoints.Num() - 1) * 2);
	triangles.Add((EnginePoints.Num() - 1) * 2 - 1);
	triangles.Add((EnginePoints.Num() - 1) * 2 + 1);

	ChartProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, false);





	/*
	
	TArray<FVector2D> Points;

	double left = -2;
	double right = 2;
	int pointsNumber = 20;
	double step = (right - left) / (pointsNumber - 1);

	for (int i = 0; i < pointsNumber; i++)
	{
		double x = left + step * i;
		double y = x * x;

		Points.Add(FVector2D(x, y));
	}

	double Xmin = DBL_MAX, Xmax = -DBL_MAX, Ymin = DBL_MAX, Ymax = -DBL_MAX;
	for (int32 i = 0; i < Points.Num(); i++)
	{
		if (Points[i].X < Xmin) { Xmin = Points[i].X; }
		if (Points[i].X > Xmax) { Xmax = Points[i].X; }
		if (Points[i].Y < Ymin) { Ymin = Points[i].Y; }
		if (Points[i].Y > Ymax) { Ymax = Points[i].Y; }
	}

	Xavailable = (XAxisLength - 1.1 * ArrowLength) * AvailableCoef;
	Yavailable = (YAxisLength - 1.1 * ArrowLength) * AvailableCoef;

	if (Xmin > 0) { Xmin = 0;  Xavailable = XAxisLength - 1.1 * ArrowLength - TextSize; }
	if (Ymin > 0) { Ymin = 0;  Yavailable = YAxisLength - 1.1 * ArrowLength - TextSize; }
	if (Xmax < 0) { Xmax = 0;  Xavailable = XAxisLength - 1.1 * ArrowLength; }
	if (Ymax < 0) { Ymax = 0;  Yavailable = YAxisLength - 1.1 * ArrowLength; }

	double Xcoef = Xavailable / abs(Xmax - Xmin);
	double Ycoef = Yavailable / abs(Ymax - Ymin);

	// FVector2D origin(TextSize + (1 - AvailableCoef) * XAxisLength / 2 - Xavailable / 2, TextSize - ArrowLength);
	// FVector2D origin(TextSize, TextSize);
	FVector2D origin(TextSize, TextSize);
	if (Xmin < 0 && Xmin < TextSize) 
	{
		origin.X = (-1) * Xmin * Xcoef; 
		origin.X += (1 - AvailableCoef) * XAxisLength / 2 + ArrowLength / 3;
	}
	if (Ymin < 0 && Ymin < TextSize) 
	{ 
		origin.Y = (-1) * Ymin * Ycoef; 
		origin.Y += (1 - AvailableCoef) * YAxisLength / 2 + ArrowLength / 3;
	}

	this->OriginSceneComponent->SetRelativeLocation(FVector(origin.X, -origin.Y, 1));

	DrawAxes(origin);

	TArray<FVector2D> EnginePoints;
	for (int i = 0; i < Points.Num(); i++)
	{
		FVector2D EnginePoint(Points[i].X * Xcoef, Points[i].Y * Ycoef);
		EnginePoints.Push(EnginePoint);
	}
	
	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	FVector2D O1O2 = FVector2D(EnginePoints[1].X - EnginePoints[0].X, EnginePoints[1].Y - EnginePoints[0].Y);
	FVector2D O2O1 = -O1O2;
	FVector2D O2O3 = FVector2D(EnginePoints[2].X - EnginePoints[1].X, EnginePoints[2].Y - EnginePoints[1].Y);
	FVector2D O3O2 = -O2O3;
	FVector2D O1O2_normal = O1O2.GetSafeNormal();
	FVector2D topLeft, bottomLeft, topRight, bottomRight;
	topLeft = FVector2D(-O1O2_normal.Y, O1O2_normal.X) * ChartThickness / 2 + EnginePoints[0];
	bottomLeft = FVector2D(O1O2_normal.Y, -O1O2_normal.X) * ChartThickness / 2 + EnginePoints[0];

	float cos2a = FVector2D::DotProduct(O2O1, O2O3) / (O2O1.Size() * O2O3.Size());
	float sina = sqrt((1 - cos2a) / 2);
	float x = ChartThickness / 2 / sina;
	FVector2D biss = x * (O2O1.GetSafeNormal() + O2O3.GetSafeNormal()).GetSafeNormal();

	if (biss.Y > 0)
	{
		topRight = FVector2D(EnginePoints[1].X + biss.X, EnginePoints[1].Y + biss.Y);
		bottomRight = FVector2D(EnginePoints[1].X - biss.X, EnginePoints[1].Y - biss.Y);
	}
	else
	{
		topRight = FVector2D(EnginePoints[1].X - biss.X, EnginePoints[1].Y - biss.Y);
		bottomRight = FVector2D(EnginePoints[1].X + biss.X, EnginePoints[1].Y + biss.Y);
	}

	vertices.Add(FVector(bottomLeft.X, -bottomLeft.Y, 0));
	vertices.Add(FVector(topLeft.X, -topLeft.Y, 0));
	vertices.Add(FVector(topRight.X, -topRight.Y, 0));
	vertices.Add(FVector(bottomRight.X, -bottomRight.Y, 0));

	triangles.Add(0);
	triangles.Add(2);
	triangles.Add(1);
	triangles.Add(2);
	triangles.Add(0);
	triangles.Add(3);

	for (int i = 2; i < EnginePoints.Num() - 1; i++)
	{
		O1O2 = O2O3;
		O2O1 = -O1O2;
		O2O3 = FVector2D(EnginePoints[i + 1].X - EnginePoints[i].X, EnginePoints[i + 1].Y - EnginePoints[i].Y);
		O3O2 = -O2O3;
		bottomLeft = bottomRight;
		topLeft = topRight;

		cos2a = FVector2D::DotProduct(O2O1, O2O3) / (O2O1.Size() * O2O3.Size());
		sina = sqrt((1 - cos2a) / 2);
		x = ChartThickness / 2 / sina;
		biss = x * (O2O1.GetSafeNormal() + O2O3.GetSafeNormal()).GetSafeNormal();
	
		if (biss.Y > 0)
		{
			topRight = FVector2D(EnginePoints[i].X + biss.X, EnginePoints[i].Y + biss.Y);
			bottomRight = FVector2D(EnginePoints[i].X - biss.X, EnginePoints[i].Y - biss.Y);
		}
		else
		{
			topRight = FVector2D(EnginePoints[i].X - biss.X, EnginePoints[i].Y - biss.Y);
			bottomRight = FVector2D(EnginePoints[i].X + biss.X, EnginePoints[i].Y + biss.Y);
		}

		vertices.Add(FVector(topRight.X, -topRight.Y, 0));
		vertices.Add(FVector(bottomRight.X, -bottomRight.Y, 0));

		triangles.Add(i * 2 - 1);
		triangles.Add(i * 2);
		triangles.Add(i * 2 - 2);

		triangles.Add(i * 2 );
		triangles.Add(i * 2 - 1);
		triangles.Add(i * 2 + 1);
	}

	O1O2 = O2O3;
	O2O1 = -O1O2;
	bottomLeft = bottomRight;
	topLeft = topRight;
	O1O2_normal = O1O2.GetSafeNormal();
	topRight = FVector2D(-O1O2_normal.Y, O1O2_normal.X) * ChartThickness / 2 + EnginePoints[EnginePoints.Num() - 1];
	bottomRight = FVector2D(O1O2_normal.Y, -O1O2_normal.X) * ChartThickness / 2 + EnginePoints[EnginePoints.Num() - 1];

	vertices.Add(FVector(topRight.X, -topRight.Y, 0));
	vertices.Add(FVector(bottomRight.X, -bottomRight.Y, 0));

	triangles.Add((EnginePoints.Num() - 1) * 2 - 1);
	triangles.Add((EnginePoints.Num() - 1) * 2);
	triangles.Add((EnginePoints.Num() - 1) * 2 - 2);

	triangles.Add((EnginePoints.Num() - 1) * 2);
	triangles.Add((EnginePoints.Num() - 1) * 2 - 1);
	triangles.Add((EnginePoints.Num() - 1) * 2 + 1);
	
	ChartProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, false);

	*/
	DrawInscription(Points, EnginePoints, origin);
}

bool CanDrawMore(float val, float border)
{
	if (border <= 0) { return val < border; }
	return val > border; 
}

void UChartPrimitiveComponent::DrawInscription(TArray<FVector2D> Points, TArray<FVector2D> EnginePoints, FVector2D origin)
{
	FRotator TextRotation(90, 90, 0);

	FVector Xlocation(XAxisLength - origin.X, ChartThickness / 2 + TextSize / 2, 1);
	UTextRenderComponent* Xinscription = NewObject<UTextRenderComponent>(this, TEXT("Xinscription"));
	Xinscription->SetupAttachment(OriginSceneComponent);
	Xinscription->SetWorldSize(TextSize);
	Xinscription->SetRelativeLocationAndRotation(Xlocation, TextRotation);
	Xinscription->SetHorizontalAlignment(EHTA_Center);
	Xinscription->SetVerticalAlignment(EVRTA_TextCenter);
	Xinscription->SetTextRenderColor(TextColor);
	Xinscription->SetText(TEXT("x"));

	FVector Ylocation(-ChartThickness / 2 - TextSize / 2, -(YAxisLength - origin.Y), 1);
	UTextRenderComponent* Yinscription = NewObject<UTextRenderComponent>(this, TEXT("Yinscription"));
	Yinscription->SetupAttachment(OriginSceneComponent);
	Yinscription->SetWorldSize(TextSize);
	Yinscription->SetRelativeLocationAndRotation(Ylocation, TextRotation);
	Yinscription->SetHorizontalAlignment(EHTA_Center);
	Yinscription->SetVerticalAlignment(EVRTA_TextCenter);
	Yinscription->SetTextRenderColor(TextColor);
	Yinscription->SetText(TEXT("y"));

	FVector ZeroLocation(-ChartThickness / 2 - TextSize / 3, ChartThickness / 2 + TextSize / 2, 1);
	UTextRenderComponent* ZeroInscription = NewObject<UTextRenderComponent>(this, TEXT("ZeroInscription"));
	ZeroInscription->SetupAttachment(OriginSceneComponent);
	ZeroInscription->SetWorldSize(NumberSize);
	ZeroInscription->SetRelativeLocationAndRotation(ZeroLocation, TextRotation);
	ZeroInscription->SetHorizontalAlignment(EHTA_Center);
	ZeroInscription->SetVerticalAlignment(EVRTA_TextCenter);
	ZeroInscription->SetTextRenderColor(TextColor);
	ZeroInscription->SetText(TEXT("0"));

	UProceduralMeshComponent *pmc = NewObject<UProceduralMeshComponent>(this, TEXT("DottedLineProceduralMesh"));
	pmc->SetupAttachment(OriginSceneComponent);

	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	int i = 0;
	for (int j = 0; j < EnginePoints.Num(); j++)
	{
		FVector2D enginePoint = EnginePoints[j];
		enginePoint.Y *= (-1);
		// vertical line
		float border = (enginePoint.Y > 0) ? AxesThickness / 2 : -AxesThickness / 2;
		while (CanDrawMore(enginePoint.Y, border))
		{
			if (border < 0)
			{
				vertices.Add(FVector(enginePoint.X - DottedLineWidth / 2, enginePoint.Y, 0)); // top left
				vertices.Add(FVector(enginePoint.X + DottedLineWidth / 2, enginePoint.Y, 0)); // top right
				vertices.Add(FVector(enginePoint.X + DottedLineWidth / 2, enginePoint.Y + DottedLineLength, 0)); // bottom right
				vertices.Add(FVector(enginePoint.X - DottedLineWidth / 2, enginePoint.Y + DottedLineLength, 0)); // bottom left
				enginePoint.Y += DottedLineLength + DottedLineGap;
			}
			else
			{
				vertices.Add(FVector(enginePoint.X - DottedLineWidth / 2, enginePoint.Y - DottedLineLength, 0)); // top left
				vertices.Add(FVector(enginePoint.X + DottedLineWidth / 2, enginePoint.Y - DottedLineLength, 0)); // top right
				vertices.Add(FVector(enginePoint.X + DottedLineWidth / 2, enginePoint.Y, 0)); // bottom right
				vertices.Add(FVector(enginePoint.X - DottedLineWidth / 2, enginePoint.Y, 0)); // bottom left
				enginePoint.Y -= DottedLineLength + DottedLineGap;
			}
			triangles.Add(i);
			triangles.Add(i + 2);
			triangles.Add(i + 1);

			triangles.Add(i + 2);
			triangles.Add(i);
			triangles.Add(i + 3);

			i += 4;
		}

		vertices.Add(FVector(enginePoint.X - DottedLineWidth / 2, -AxesThickness, 0)); // top left
		vertices.Add(FVector(enginePoint.X + DottedLineWidth / 2, -AxesThickness, 0)); // top right
		vertices.Add(FVector(enginePoint.X + DottedLineWidth / 2, AxesThickness, 0)); // bottom right
		vertices.Add(FVector(enginePoint.X - DottedLineWidth / 2, AxesThickness, 0)); // bottom left

		triangles.Add(i);
		triangles.Add(i + 2);
		triangles.Add(i + 1);

		triangles.Add(i + 2);
		triangles.Add(i);
		triangles.Add(i + 3);

		i += 4;

		// horizontal line
		enginePoint = EnginePoints[j];
		enginePoint.Y *= (-1);
		border = (enginePoint.X > 0) ? AxesThickness / 2 : -AxesThickness / 2;
		while (CanDrawMore(enginePoint.X, border))
		{
			if (border < 0)
			{
				vertices.Add(FVector(enginePoint.X, enginePoint.Y - DottedLineWidth / 2, 0)); // top left
				vertices.Add(FVector(enginePoint.X + DottedLineLength, enginePoint.Y - DottedLineWidth / 2, 0)); // top right
				vertices.Add(FVector(enginePoint.X + DottedLineLength, enginePoint.Y + DottedLineWidth / 2, 0)); // bottom right
				vertices.Add(FVector(enginePoint.X, enginePoint.Y + DottedLineWidth / 2, 0)); // bottom left
				enginePoint.X += DottedLineLength + DottedLineGap;
			}
			else
			{
				vertices.Add(FVector(enginePoint.X - DottedLineLength, enginePoint.Y - DottedLineWidth / 2, 0)); // top left
				vertices.Add(FVector(enginePoint.X, enginePoint.Y - DottedLineWidth / 2, 0)); // top right
				vertices.Add(FVector(enginePoint.X, enginePoint.Y + DottedLineWidth / 2, 0)); // bottom right
				vertices.Add(FVector(enginePoint.X - DottedLineLength, enginePoint.Y + DottedLineWidth / 2, 0)); // bottom left
				enginePoint.X -= DottedLineLength + DottedLineGap;
			}
			triangles.Add(i);
			triangles.Add(i + 2);
			triangles.Add(i + 1);

			triangles.Add(i + 2);
			triangles.Add(i);
			triangles.Add(i + 3);

			i += 4;
		}

		vertices.Add(FVector(-AxesThickness, enginePoint.Y - DottedLineWidth / 2, 0)); // top left
		vertices.Add(FVector(AxesThickness, enginePoint.Y - DottedLineWidth / 2, 0)); // top right
		vertices.Add(FVector(AxesThickness, enginePoint.Y + DottedLineWidth / 2, 0)); // bottom right
		vertices.Add(FVector(-AxesThickness, enginePoint.Y + DottedLineWidth / 2, 0)); // bottom left

		triangles.Add(i);
		triangles.Add(i + 2);
		triangles.Add(i + 1);

		triangles.Add(i + 2);
		triangles.Add(i);
		triangles.Add(i + 3);

		i += 4;
	}
	pmc->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, false);
	DrawNumbers(Points, EnginePoints, origin);
}

void UChartPrimitiveComponent::DrawNumbers(TArray<FVector2D> Points, TArray<FVector2D> EnginePoints, FVector2D origin)
{
	FRotator TextRotation(90, 90, 0);
	for (int i = 0; i < EnginePoints.Num(); i++)
	{
		UTextRenderComponent* number = NewObject<UTextRenderComponent>(this, *FString("x" + FString::FromInt(i)));
		FVector locationX(EnginePoints[i].X, ChartThickness / 2 + TextWidth, 1);
		number->SetupAttachment(OriginSceneComponent);
		number->SetWorldSize(NumberSize);
		number->SetRelativeLocationAndRotation(locationX, TextRotation);
		number->SetHorizontalAlignment(EHTA_Center);
		number->SetVerticalAlignment(EVRTA_TextCenter);
		number->SetTextRenderColor(NumberColor);
		number->SetText(FString::SanitizeFloat(Points[i].X));

		int32 numberOfSymbols = FString::SanitizeFloat(Points[i].Y).Len();
		number = NewObject<UTextRenderComponent>(this, *FString("y" + FString::FromInt(i)));
		FVector locationY(-ChartThickness / 2 - NumberWidth * numberOfSymbols / 2.0, -EnginePoints[i].Y, 1);
		number->SetupAttachment(OriginSceneComponent);
		number->SetWorldSize(NumberSize);
		number->SetRelativeLocationAndRotation(locationY, TextRotation);
		number->SetHorizontalAlignment(EHTA_Center);
		number->SetVerticalAlignment(EVRTA_TextCenter);
		number->SetTextRenderColor(NumberColor);
		number->SetText(FString::SanitizeFloat(Points[i].Y));
	}
}

void UChartPrimitiveComponent::DrawAxes(FVector2D origin)
{
	TArray<FVector> vertices;
	// axis Y
	vertices.Add(FVector(origin.X - AxesThickness / 2, 0, 0));
	vertices.Add(FVector(origin.X - AxesThickness / 2, -YAxisLength, 0));
	vertices.Add(FVector(origin.X + AxesThickness / 2, -YAxisLength, 0));
	vertices.Add(FVector(origin.X + AxesThickness / 2, 0, 0));

	// axis X
	vertices.Add(FVector(0, -origin.Y - AxesThickness / 2, 0));
	vertices.Add(FVector(XAxisLength, -origin.Y - AxesThickness / 2, 0));
	vertices.Add(FVector(XAxisLength, -origin.Y + AxesThickness / 2, 0));
	vertices.Add(FVector(0, -origin.Y + AxesThickness / 2, 0));
	
	// arrows on the axis Y
	float yAxisArrow_Mid = -YAxisLength + 0.16 * ArrowLength;
	float yAxisArrow_Bottom = -YAxisLength + 0.5 * ArrowLength;
	float yAxisArrow_Top = -YAxisLength - 0.5 * ArrowLength;
	float yAxisArrow_Left = origin.X - AxesThickness / 2 - ArrowWidth / 2;
	float yAxisArrow_Right = origin.X + AxesThickness / 2 + ArrowWidth / 2;

	vertices.Add(FVector(origin.X, yAxisArrow_Mid, 0));
	vertices.Add(FVector(origin.X, yAxisArrow_Top, 0));
	vertices.Add(FVector(yAxisArrow_Left, yAxisArrow_Bottom, 0));
	vertices.Add(FVector(yAxisArrow_Right, yAxisArrow_Bottom, 0));

	// arrows on the axis X
	float xAxisArrow_Mid = XAxisLength - 0.16 * ArrowLength;
	float xAxisArrow_Left = XAxisLength - 0.5 * ArrowLength;
	float xAxisArrow_Right = XAxisLength + 0.5 * ArrowLength;
	float xAxisArrow_Top = -origin.Y - AxesThickness / 2 - ArrowWidth / 2;
	float xAxisArrow_Bottom = -origin.Y + AxesThickness / 2 + ArrowWidth / 2;

	vertices.Add(FVector(xAxisArrow_Mid, -origin.Y, 0));
	vertices.Add(FVector(xAxisArrow_Right, -origin.Y, 0));
	vertices.Add(FVector(xAxisArrow_Left, xAxisArrow_Top, 0));
	vertices.Add(FVector(xAxisArrow_Left, xAxisArrow_Bottom, 0));

	TArray<int32> triangles;
	// y axis
	triangles.Add(0);
	triangles.Add(3);
	triangles.Add(1);
	triangles.Add(1);
	triangles.Add(3);
	triangles.Add(2);

	// x axis
	triangles.Add(4);
	triangles.Add(7);
	triangles.Add(5);
	triangles.Add(5);
	triangles.Add(7);
	triangles.Add(6);

	// y arrow
	triangles.Add(10);
	triangles.Add(8);
	triangles.Add(9);
	triangles.Add(8);
	triangles.Add(11);
	triangles.Add(9);

	// x arrow
	triangles.Add(14);
	triangles.Add(12);
	triangles.Add(13);
	triangles.Add(12);
	triangles.Add(15);
	triangles.Add(13);

	TArray<FVector> normals;
	TArray<FVector2D> UV0;
	/*
	UV0.Add(FVector2D(0, 1));
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(1, 0));
	UV0.Add(FVector2D(1, 1));

	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(1, 0));
	UV0.Add(FVector2D(1, 1));
	UV0.Add(FVector2D(0, 1));
	*/
	/*
	UV0.Add(FVector2D(0, 0));
	UV0.Add(FVector2D(1, 0));
	UV0.Add(FVector2D(1, 1));
	UV0.Add(FVector2D(0, 1));
	*/

	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	ChartAxesProceduralMesh->CreateMeshSection_LinearColor(0, vertices, triangles, normals, UV0, vertexColors, tangents, false);

	const ConstructorHelpers::FObjectFinder<UMaterial> ChartMaterial = (TEXT("/Game/MyContent/Materials/M_Chart"));
	if (ChartMaterial.Succeeded())
	{
		ChartAxesProceduralMesh->SetMaterial(0, ChartMaterial.Object);
	}
}