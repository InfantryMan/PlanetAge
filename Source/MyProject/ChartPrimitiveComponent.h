// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "ChartPrimitiveComponent.generated.h"

const int32 DEFAULT_RECT_HEIGHT = 125;
const int32 DEFAULT_RECT_WIDTH = 150;
const int32 DEFAULT_OFFSET = 5;
const int32 DEFAULT_AXES_THICKNESS = 4;
const int32 DEFAULT_CHART_THICKNESS = 3;
const int32 DEFAULT_ARROW_LENGTH = 20;
const int32 DEFAULT_ARROW_WIDTH = 2 * DEFAULT_AXES_THICKNESS;

/**
 * 
 */
UCLASS()
class MYPROJECT_API UChartPrimitiveComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

private:
	int32 RectHeight;
	int32 RectWidth;

	int32 Offset;
	int32 AxesThickness;
	int32 ChartThickness;

	int32 ArrowLength;
	int32 ArrowWidth;

public:
	UChartPrimitiveComponent();
	~UChartPrimitiveComponent();
	UChartPrimitiveComponent(int32 _rectHeight, int32 _rectWidth, int32 _offset, int32 _axesThickness, int32 _chartThickness, int32 _arrowLength, int32 _arrowWidth);
	
	void SetupGeometry();
	void DrawRectangle();
	void DrawAxes();

public:
	UPROPERTY(EditAnywhere)
		UProceduralMeshComponent *ChartAxesProceduralMesh;

	UPROPERTY(EditAnywhere)
		UProceduralMeshComponent *ChartProceduralMesh;

	UPROPERTY(EditAnywhere)
		UProceduralMeshComponent *RectangleProceduralMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent *ChartSceneComponent;

	UPROPERTY(EditAnywhere)
		USceneComponent *RectangleSceneComponent;

	int32 GetRectHeight() const { return RectHeight; }
	void SetRectHeight(int32 val) { RectHeight = val; }

	int32 GetRectWidth() const { return RectWidth; }
	void SetRectWidth(int32 val) { RectWidth = val; }

	int32 GetOffset() const { return Offset; }
	void SetOffset(int32 val) { Offset = val; }

	int32 GetAxesThickness() const { return AxesThickness; }
	void SetAxesThickness(int32 val) { AxesThickness = val; }

	int32 GetChartThickness() const { return ChartThickness; }
	void SetChartThickness(int32 val) { ChartThickness = val; }

	int32 GetArrowLength() const { return ArrowLength; }
	void SetArrowLength(int32 val) { ArrowLength = val; }

	int32 GetArrowWidth() const { return ArrowWidth; }
	void SetArrowWidth(int32 val) { ArrowWidth = val; }

};
