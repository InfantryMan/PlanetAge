// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "ChartPrimitiveComponent.generated.h"

const float DEFAULT_RECT_HEIGHT = 125;
const float DEFAULT_RECT_WIDTH = 150;
const float DEFAULT_OFFSET = 10;
const float DEFAULT_AXES_THICKNESS = 2;
const float DEFAULT_CHART_THICKNESS = 2;
const float DEFAULT_ARROW_LENGTH = 8;
const float DEFAULT_ARROW_WIDTH = 2 * DEFAULT_AXES_THICKNESS;
const float DEFAULT_AVAILABLE_COEF = 0.9;

const float DEFAULT_TEXT_SIZE = 14;
const float DEFAULT_TEXT_WIDTH = DEFAULT_TEXT_SIZE / 2;
const FColor DEFAULT_TEXT_COLOR = FColor(0, 0, 0);

const float DEFAULT_NUMBER_SIZE = 10;
const float DEFAULT_NUMBER_WIDTH = DEFAULT_NUMBER_SIZE / 1.5;
const FColor DEFAULT_NUMBER_COLOR = FColor(0, 0, 0);

const float DEFAULT_DOTTED_LINE_WIDTH = 1;
const float DEFAULT_DOTTED_LINE_LENGTH = 2;
const float DEFAULT_DOTTED_LINE_GAP = 1.5;


/**
 * 
 */
UCLASS()
class MYPROJECT_API UChartPrimitiveComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

private:
	float RectHeight;
	float RectWidth;
	float Offset;
	float AvailableCoef;
	float XAxisLength;
	float YAxisLength;
	float Xavailable;
	float Yavailable;


	float AxesThickness;
	float ChartThickness;

	float ArrowLength;
	float ArrowWidth;

	float TextSize;
	float TextWidth;
	FColor TextColor;

	float NumberSize;
	float NumberWidth;
	FColor NumberColor;

	float DottedLineWidth;
	float DottedLineLength;
	float DottedLineGap;

public:
	UChartPrimitiveComponent();
	~UChartPrimitiveComponent();
	UChartPrimitiveComponent(int32 _rectHeight, int32 _rectWidth, int32 _offset, int32 _axesThickness, int32 _chartThickness, int32 _arrowLength, int32 _arrowWidth);
	
	void SetupGeometry();
	void DrawRectangle();
	void DrawAxes(FVector2D origin);
	UFUNCTION(BlueprintCallable)
	void DrawBisChart();
	void DrawOrtChart(TArray<FVector2D> Points);
	void DrawInscription(TArray<FVector2D> Points, TArray<FVector2D> EnginePoints, FVector2D origin);
	void DrawNumbers(TArray<FVector2D> Points, TArray<FVector2D> EnginePoints, FVector2D origin);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UProceduralMeshComponent *ChartAxesProceduralMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UProceduralMeshComponent *ChartProceduralMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UProceduralMeshComponent *RectangleProceduralMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USceneComponent *ChartSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USceneComponent *OriginSceneComponent;

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
