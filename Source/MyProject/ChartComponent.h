// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Components/ActorComponent.h"
#include "ChartComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UChartComponent : public UActorComponent
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
	// Sets default values for this component's properties
	UChartComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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
