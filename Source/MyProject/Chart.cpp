#include "Chart.h"

Chart::Chart():
	RectHeight(DEFAULT_RECT_HEIGHT),
	RectWidth(DEFAULT_RECT_WIDTH),
	Offset(DEFAULT_OFFSET),
	AxesThickness(DEFAULT_AXES_THICKNESS),
	ChartThickness(DEFAULT_CHART_THICKNESS),
	ArrowLength(DEFAULT_ARROW_LENGTH),
	ArrowWidth(DEFAULT_ARROW_WIDTH)
{
}

Chart::~Chart()
{
}

Chart::Chart(int32 _rectHeight, int32 _rectWidth, int32 _offset, int32 _axesThickness, int32 _chartThickness, int32 _arrowLength, int32 _arrowWidth):
	RectHeight(_rectHeight),
	RectWidth(_rectWidth),
	Offset(_offset),
	AxesThickness(_axesThickness),
	ChartThickness(_chartThickness),
	ArrowLength(_arrowLength),
	ArrowWidth(_arrowWidth)
{
}

void Chart::SetupGeometry(USceneComponent *RootComponent, FVector RectanglePosition)
{
// 	this->ChartAxesProceduralMesh	= CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ChartAxesProceduralMesh"));
// 	this->ChartProceduralMesh		= CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ChartProceduralMesh"));
// 	this->RectangleProceduralMesh	= CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RectangleProceduralMesh"));
// 
// 	this->RectangleSceneComponent	= CreateDefaultSubobject<USceneComponent>(TEXT("RectangleSceneComponent"));
// 	this->RectangleSceneComponent->AttachTo(RootComponent);
// 	this->RectangleSceneComponent->SetRelativeLocation(RectanglePosition);
// 
// 
// 	this->ChartAxesSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChartAxesSceneComponent"));
// 	this->ChartAxesSceneComponent->AttachTo(RootComponent);
// 	this->ChartAxesSceneComponent->SetRelativeLocation(FVector(-290, 17.5, 22));
// 	
// 	this->ChartAxesProceduralMesh->SetupAttachment(ChartAxesSceneComponent);
// 
// 	this->ChartSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ChartSceneComponent"));
// 	this->ChartSceneComponent->AttachTo(RootComponent);
// 	this->ChartSceneComponent->SetRelativeLocation(FVector(-290 + ChartThickness, 17.5 + ChartThickness, 22));
// 	
// 	this->ChartProceduralMesh->SetupAttachment(ChartSceneComponent);
}