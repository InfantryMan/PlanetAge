// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ChartPrimitiveComponent.h"
#include "PlanetCoefficientValues.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

#include "GameCardView.generated.h"

const FVector DEFAULT_CHART_POSITION_ = FVector(-290, 17.5, 22);
const FVector DEFAULT_CHART_POSITION = FVector(18, 290, 21.5);


UCLASS()
class MYPROJECT_API AGameCardView : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCardView();
	static void AddVertex(TArray<FVector> & Vertices, FVector const& Vect);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Size of GameCard
	static const int XCardSize = 488;
	static const int YCardSize = 302;
	static const int ZCardSize = 30;
	static const int XLeftSideCardSize = 182;
	static const int XRightSizeCardSize = XCardSize - XLeftSideCardSize;

	FTimerHandle TimerHandle;
	UFUNCTION()
		void OnTimerEnd();

	// Chart position
	FVector ChartPosition;

	// Meshes:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent *CardMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		UStaticMeshComponent *PlanetMesh;

	UPROPERTY(EditAnywhere)
		FPlanetCoefficientValues Coeffs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChartPrimitiveComponent *ChartPrimitiveComponent;
};
