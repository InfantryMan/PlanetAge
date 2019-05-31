// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PlanetCoefficientValues.h"

#include "GameCardView.generated.h"

UCLASS()
class MYPROJECT_API AGameCardView : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCardView();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Size of GameCard
	static const int xCardSize = 488;
	static const int yCardSize = 302;
	static const int zCardSize = 30;
	static const int xLeftSideCardSize = 182;
	static const int xRightSizeCardSize = xCardSize - xLeftSideCardSize;

	// Chart 
	static const int32 lengthOfAxisY = 125;
	static const int32 lengthOfAxisX = 150;
	static const int32 thicknessOfAxes = 4;
	static const int32 lengthOfArrow = 20;
	static const int32 widthOfArrow = 2 * thicknessOfAxes;

	static const int32 thicknessOfChart = 1;


	// Meshes:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent *CardMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent *PlanetMesh;

	UPROPERTY(EditAnywhere)
		FPlanetCoefficientValues Coeffs;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent *ChartAxesProceduralMesh;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent *ChartProceduralMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent *ChartAxesSceneComponent;

	UPROPERTY(EditAnywhere)
		USceneComponent *ChartSceneComponent;

	UFUNCTION(BlueprintCallable)
		void drawChart();
};
