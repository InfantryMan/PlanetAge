#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"

const int32 DEFAULT_RECT_HEIGHT = 125;
const int32 DEFAULT_RECT_WIDTH = 150;
const int32 DEFAULT_OFFSET = 5;
const int32 DEFAULT_AXES_THICKNESS = 4;
const int32 DEFAULT_CHART_THICKNESS = 3;
const int32 DEFAULT_ARROW_LENGTH = 20;
const int32 DEFAULT_ARROW_WIDTH = 2 * DEFAULT_AXES_THICKNESS;

class MYPROJECT_API Chart : public UActorComponent
{
private:
	int32 RectHeight;
	int32 RectWidth;

	int32 Offset;
	int32 AxesThickness;
	int32 ChartThickness;

	int32 ArrowLength;
	int32 ArrowWidth;

public:
	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent *ChartAxesProceduralMesh;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent *ChartProceduralMesh;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent *RectangleProceduralMesh;

	UPROPERTY(VisibleAnywhere)
		USceneComponent *ChartAxesSceneComponent;

	UPROPERTY(VisibleAnywhere)
		USceneComponent *ChartSceneComponent;

	UPROPERTY(VisibleAnywhere)
		USceneComponent *RectangleSceneComponent;

	Chart();

	Chart(int32 _rectHeight, int32 _rectWidth, int32 _offset, int32 _axesThickness, int32 _chartThickness, int32 _arrowLength, int32 _arrowWidth);

	~Chart();

	void SetupGeometry(USceneComponent *RootComponent, FVector RectanglePosition);
	
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

